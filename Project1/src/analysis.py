import numpy as np
import subprocess
from numba import jit
from tqdm import tqdm


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


def runner(conf):
    args = ["./vmc", "numPart", "numDim",
            "numSteps", "stepLength", "alpha", "a", "omega"]
    for i in range(1, len(args)):
        args[i] = str(conf[args[i]])

    popen = subprocess.Popen(args, stdout=subprocess.PIPE)
    assert (popen.wait() == 0)


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
        x =\
            (bins[:-1, None, None] < pos[:, :, 0]) &\
            (pos[:, :, 0] < bins[1:, None, None])

        count = np.sum(x, axis=(1, 2)) / pos.shape[0]
        return count

    if mode == "2D":
        count = np.zeros((bins.shape[0], bins.shape[0]))
        y_min = x_min = bins[0]
        dy = dx = bins[1] - bins[0]
        for x, y in tqdm(pos):
            try:
                count[int((x - x_min) // dx), int((y - y_min) // dy)] += 1
            except:
                pass

        return count


def blocking(x):
    x_blocked = [np.mean(i) for i in x.reshape(-1, 2)]
    return np.array(x_blocked)
