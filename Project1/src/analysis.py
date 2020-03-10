import numpy as np
import subprocess
from numba import jit


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
    args = ["./vmc", "numPart", "numDim", "numSteps", "stepLength", "alpha"]
    for i in range(1, len(args)):
        args[i] = str(conf[args[i]])

    popen = subprocess.Popen(args, stdout=subprocess.PIPE)
    assert (popen.wait() == 0)


def statistics(localEnergies):

    cutoff = thermalize_cutoff(localEnergies, 10000, 0.001)
    meanE = np.mean(localEnergies[cutoff:])
    varE = np.var(localEnergies[cutoff:])

    return meanE, varE


def oneBodyDensity(configurations, bins):
    count = np.zeros(bins.shape[0])

    for config in configurations:
        for particlePos in config:
            r = np.linalg.norm(particlePos)
            ting = (bins[:-1] < r) & (r < bins[1:])
            count[np.where(ting)[0]] += 1
    return count / configurations.shape[0]


def blocking(x):
    x_blocked = [np.mean(i) for i in x.reshape(-1, 2)]
    return np.array(x_blocked)
