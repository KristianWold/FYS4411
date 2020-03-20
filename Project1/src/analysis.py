import numpy as np
import subprocess
from tqdm import tqdm
import os
import shutil
import multiprocessing
import pandas as pd


def smoothing(x, smoothing_window):
    """Return smoothed version of x by averaging
    values in an interval of length smoothing_window
    """

    x_smooth = np.zeros(x.shape)
    for i in range(len(x) - smoothing_window - 1):
        x_smooth[i] = np.mean(x[i:i + smoothing_window])

    return x_smooth


def derivative(y, dx=1):
    """Return derivative of y"""

    return (y[1:] - y[:-1]) / dx


def thermalize_cutoff(localEnergies, smoothing_window, tol):
    """Return position where system is thermalized
    according to some tolerance tol, based on the derivative
    of the smoothed local energies
    """
    mean = np.mean(localEnergies)
    smoothLocalEnergies = smoothing(localEnergies, smoothing_window)
    check_slope = derivative(smoothLocalEnergies) < tol
    cutoff = np.where(check_slope)[0][0]

    return cutoff


def setupDictionaries():

    # Maps system object types to numbers for the executable to interpret
    mapper = {}
    mapper["RandomUniform"] = "1"
    mapper["HardshellInitial"] = "2"

    mapper["SimpleGaussian"] = "1"
    mapper["SimpleGaussianNumerical"] = "2"
    mapper["HardshellWavefunction"] = "3"
    mapper["EllipticalHardshellWavefunction"] = "4"

    mapper["HarmonicOscillator"] = "1"
    mapper["EllipticalOscillator"] = "2"

    # Arguments expected by the executable
    params = ["numPart", "numDim", "numSteps", "stepLength", "importanceSampling",
              "alpha", "a", "omega",
              "InitialState", "Wavefunction", "Hamiltonian"]

    return mapper, params


def config():
    # Default values
    default = {}
    default["directory"] = "data"
    default["threads"] = 1
    default["numPart"] = 1
    default["numDim"] = 1
    default["numSteps"] = 1000
    default["stepLength"] = 1
    default["importanceSampling"] = 0
    default["alpha"] = 0.5
    default["a"] = 1
    default["omega"] = 1
    default["InitialState"] = "RandomUniform"
    default["Wavefunction"] = "SimpleGaussian"
    default["Hamiltonian"] = "HarmonicOscillator"
    return default


def runner(conf, verbose=False):

    mapper, params = setupDictionaries()

    dir = conf["directory"]
    if os.path.exists(dir):
        shutil.rmtree(dir)
    os.mkdir(dir)

    for i in range(len(params)):
        params[i] = str(conf[params[i]])

    args = []
    numThreads = conf["threads"]
    for i in range(numThreads):
        args.append(
            ["./vmc", conf["directory"], str(i)]
            + params[:8] + [mapper[i] for i in params[8:]]
        )

    if verbose:
        print(f"Starting simulation")
        print(f"numPart: {params[0]}")
        print(f"numDim: {params[1]}")
        print(f"numSteps: {params[2]}")
        print(f"stepLength: {params[3]}")
        print(f"importanceSampling: {params[4]}")
        print(f"alpha: {params[5]}")
        print(f"a: {params[6]}")
        print(f"omega: {params[7]}")
        print(f"InitialState: {params[8]}")
        print(f"WaveFunction: {params[9]}")
        print(f"Hamiltonian: {params[10]}")

    processes = []
    for a in args:
        process = subprocess.Popen(a, stdout=subprocess.PIPE)
        processes.append(process)

    for process in processes:
        assert (process.wait() == 0)

    if verbose:
        print("Done!")
        print("------------")


def readData(conf, cutoff=0):
    localEnergies = []
    pos = []
    gradient = 0
    acceptanceRate = 0
    for i in range(conf["threads"]):

        localEnergies_temp = pd.read_csv(
            f"{conf['directory']}/localEnergies_{i}.txt", sep="\n", header=None
        ).values
        localEnergies.append(localEnergies_temp[cutoff:])

        pos_temp = pd.read_csv(
            f"{conf['directory']}/configuration_{i}.txt", sep="\n", header=None
        ).values
        pos.append(pos_temp.reshape(-1, conf["numDim"])[cutoff:])

        gradient_temp = pd.read_csv(
            f"{conf['directory']}/gradient_{i}.txt", sep="\n", header=None
        ).values

        gradient += 2 * np.mean(localEnergies[i] * gradient_temp)
        gradient += -2 * np.mean(localEnergies[i]) * np.mean(gradient_temp)

        acceptanceRate_temp = pd.read_csv(
            f"{conf['directory']}/metadata_{i}.txt", sep="\n", header=None
        ).values
        acceptanceRate += acceptanceRate_temp[0]

    gradient /= conf["threads"]
    acceptanceRate /= conf["threads"]

    return localEnergies, pos, gradient, acceptanceRate


def oneBodyDensity(pos, bins, mode="radial"):

    if mode == "radial":
        r = np.linalg.norm(pos, axis=2)
        ting = (bins[:-1, None, None] < r) & (r < bins[1:, None, None])
        print(ting.shape)
        count = np.sum(ting, axis=(1, 2)) / pos.shape[0]
        return count

    if mode == "1D":
        count = np.zeros(bins.shape[0])
        x_min = bins[0]
        dx = bins[1] - bins[0]
        for x in tqdm(pos):
            try:
                count[int((x - x_min) // dx)] += 1
            except:
                pass

        return count / dx

    if mode == "2D":
        count = np.zeros((bins.shape[0], bins.shape[0]))
        y_min = x_min = bins[0]
        dy = dx = bins[1] - bins[0]
        for x, y in tqdm(pos):
            try:
                count[int((x - x_min) // dx), int((y - y_min) // dy)] += 1
            except:
                pass

        return count / pos.shape[0]


def blocking(x, degree=1):
    estimatedVar = [np.std(x)**2 / len(x)]
    for i in range(degree):
        x = np.array([np.mean(i) for i in x.reshape(-1, 2)])
        estimatedVar.append(np.std(x)**2 / len(x))
    return estimatedVar
