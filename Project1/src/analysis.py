import numpy as np
import subprocess
from tqdm import tqdm
import os
import shutil
import multiprocessing


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


def runner(conf, threads=1):

    dir = conf["directory"]
    if os.path.exists(dir):
        shutil.rmtree(dir)
    os.mkdir(dir)

    params = ["numPart", "numDim", "numSteps",
              "stepLength", "alpha", "a", "omega"]

    for i in range(len(params)):
        params[i] = str(conf[params[i]])

    args = []
    for i in range(threads):
        args.append(["./vmc", conf["directory"], str(i)] + params)

    processes = []
    for a in args:
        process = subprocess.Popen(a, stdout=subprocess.PIPE)
        processes.append(process)

    for process in processes:
        assert (process.wait() == 0)


def statistics(localEnergies):

    cutoff = thermalize_cutoff(localEnergies, 10000, 0.001)
    meanE = np.mean(localEnergies[cutoff:])
    varE = np.var(localEnergies[cutoff:])

    return meanE, varE


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

        return count / pos.shape[0]

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


def blocking(x):
    x_blocked = [np.mean(i) for i in x.reshape(-1, 2)]
    return np.array(x_blocked)
