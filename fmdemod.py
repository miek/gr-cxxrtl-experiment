from nmigen import *
from nmigen.back import cxxrtl

import cmath
import math

class IQ:
    def __init__(self, sample_depth):
        self.i = Signal(signed(sample_depth))
        self.q = Signal(signed(sample_depth))

class FMDemod(Elaboratable):
    def __init__(self, sample_depth, iterations=9):
        self._iterations = iterations
        self.input   = IQ(sample_depth)
        self.output  = Signal(signed(sample_depth))
        self._sample_depth = sample_depth

    def cordic_angle(self, l):
        k = pow(2, -l)
        phase_rads = cmath.phase(complex(1, k))
        return round(phase_rads * pow(2, self._sample_depth-1) / math.pi)

    def elaborate(self, platform):
        m = Module()

        stages = [IQ(self._sample_depth)             for i in range(self._iterations)]
        phases = [Signal(signed(self._sample_depth)) for i in range(self._iterations)]

        cordic_angles = [self.cordic_angle(i)        for i in range(self._iterations)]
        #print(cordic_angles)

        # First stage, special case for 90 degrees
        negative_phase = self.input.q[-1]
        with m.If(negative_phase):
            # Rotate +90 and set the initial phase estimate to -90
            m.d.sync += [
                stages[0].i.eq(-self.input.q),
                stages[0].q.eq( self.input.i),
                phases[0].eq( pow(2, self._sample_depth-2))
            ]
        with m.Else():
            # Rotate -90 and set the initial phase estimate to +90
            m.d.sync += [
                stages[0].i.eq( self.input.q),
                stages[0].q.eq(-self.input.i),
                phases[0].eq(-pow(2, self._sample_depth-2))
            ]

        # Remaining stages, rotate towards 1+0j by successively smaller angles
        for i in range(self._iterations-1):
            lhs = stages[i+1]
            rhs = stages[i]
            negative_phase = rhs.q[-1]
            with m.If(negative_phase):
                # Rotate positive towards 1+0j, subtract from phase estimate
                m.d.sync += [
                    lhs.i.eq(rhs.i - (rhs.q >> i)),
                    lhs.q.eq(rhs.q + (rhs.i >> i)),
                    phases[i+1].eq(phases[i] - cordic_angles[i]),
                ]
            with m.Else():
                # Rotate negative towards 1+0j, add to phase estimate
                m.d.sync += [
                    lhs.i.eq(rhs.i + (rhs.q >> i)),
                    lhs.q.eq(rhs.q - (rhs.i >> i)),
                    phases[i+1].eq(phases[i] + cordic_angles[i]),
                ]

        prev_phase = Signal(signed(self._sample_depth))
        m.d.sync += [
            prev_phase.eq(phases[-1]),
            self.output.eq(phases[-1] - prev_phase),
        ]

        return m


if __name__ == "__main__":
    m = Module()
    
    input_i = Signal(signed(16))
    input_q = Signal(signed(16))
    output  = Signal(signed(16))
    fmdemod = FMDemod(16)
    m.submodules += fmdemod

    blink = Signal()
    m.d.sync += blink.eq(blink + 1)

    m.d.comb += [
        fmdemod.input.i.eq(input_i),
        fmdemod.input.q.eq(input_q),
        output .eq(fmdemod.output),
    ]

    output = cxxrtl.convert(m, ports=(input_i, input_q, output, blink))
    with open('lib/rtl.cpp', 'w') as f:
        f.write(output)
