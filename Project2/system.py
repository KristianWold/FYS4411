import tensorflow as tf
import numpy as np
from tqdm.notebook import tqdm


class System():
    def __init__(self,
                 num_part,
                 dim,
                 Ansatz=None,
                 External=None,
                 Internal=None,
                 Sampler=None
                 ):
        self.num_part = num_part
        self.dim = dim

        self.Ansatz = Ansatz
        self.External = External
        self.Internal = Internal
        self.Sampler = Sampler

        self.Ansatz.system = self
        self.Sampler.system = self


class Metropolis():
    def __init__(self, step_length, steps):
        self.step_length = step_length
        self.steps = steps

    def __call__(self, batch_size):
        total_accepted = 0
        dim = self.system.dim

        # inital position for walkers
        x_old = tf.random.uniform(
            (batch_size, dim), minval=-2, maxval=2, dtype=tf.dtypes.float64)
        psi_old = self.system.Ansatz(x_old).numpy()

        # thermalizing steps
        for i in range(self.steps):
            x_new = x_old + self.step_length * \
                tf.random.uniform((batch_size, dim), minval=-1, maxval=1,
                                  dtype=tf.dtypes.float64)
            psi_new = self.system.Ansatz(x_new).numpy()

            U = np.random.uniform(0, 1, (batch_size, 1))
            # vectorized acceptance criterion
            mask = ((psi_new / psi_old)**2 > U)[:, 0]

            x_old = x_old.numpy()
            x_new = x_new.numpy()

            # update walkers
            x_old[mask] = x_new[mask]
            psi_old[mask] = psi_new[mask]
            x_old = tf.convert_to_tensor(x_old, dtype=tf.dtypes.float64)
            total_accepted += np.sum(mask)

        return x_old, total_accepted


class HarmonicOsc():
    def __init__(self, omega):
        self.omega = omega

    def __call__(self, x):
        V = 0.5 * self.omega**2 * \
            tf.reshape(tf.reduce_sum(x**2, axis=1), (-1, 1))
        return V


class Coulomb():
    def __init__(self, alpha, beta):
        self.alpha = alpha
        self.beta = beta

    def __call__(self, x, num_part, dim):
        V = 0
        for i in range(num_part):
            for j in range(i):
                r12 = tf.norm(x[:, i * dim:(i + 1) * dim] -
                              x[:, j * dim:(j + 1) * dim], axis=1)
                r12 = tf.reshape(r12, (-1, 1))
                V += self.alpha / tf.math.sqrt(r12**2 + self.beta**2)

        return V


def oneBodyDensity(pos, bins, mode="radial"):

    if mode == "radial1D":
        density = np.zeros(bins.shape[0])
        r_min = bins[0]
        dr = bins[1] - bins[0]
        rPos = np.linalg.norm(pos, axis=1)
        for r in tqdm(rPos):
            try:
                density[int((r - r_min) // dr)] += 1 / dr
            except:
                pass

        return density

    if mode == "radial2D":
        density = np.zeros(bins.shape[0])
        r_min = bins[0]
        dr = bins[1] - bins[0]
        rPos = np.linalg.norm(pos, axis=1)
        for r in tqdm(rPos):
            try:
                density[int((r - r_min) // dr)] += 1 / (2 * np.pi * dr * r)
            except:
                pass

        return density

    if mode == "radial3D":
        density = np.zeros(bins.shape[0])
        r_min = bins[0]
        dr = bins[1] - bins[0]
        rPos = np.linalg.norm(pos, axis=1)
        for r in tqdm(rPos):
            try:
                density[int((r - r_min) // dr)] += 1 / (4 * np.pi * dr * r**2)
            except:
                pass

        return density

    if mode == "1D":
        density = np.zeros(bins.shape[0])
        x_min = bins[0]
        dx = bins[1] - bins[0]
        for x in tqdm(pos):
            try:
                density[int((x - x_min) // dx)] += 1
            except:
                pass

        return density / dx

    if mode == "2D":
        density = np.zeros((bins.shape[0], bins.shape[0]))
        y_min = x_min = bins[0]
        dy = dx = bins[1] - bins[0]
        for x, y in tqdm(pos):
            try:
                density[int((x - x_min) // dx), int((y - y_min) // dy)] += 1
            except:
                pass

        return density / pos.shape[0]
