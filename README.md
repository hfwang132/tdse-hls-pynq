# TDSE on PYNQ via HLS

This is homework for 2022 AMD-Xilinx Summer School. DFT and TDSE have been realized on pynq.

## Repository Tree

```
.
├── README.md
├── dft
│   ├── jupyter
│   ├── overlay
│   ├── report
│   └── src
└── tdse
    ├── jupyter
    ├── overlay
    ├── report
    └── src

```

## DFT (Discrete Fourier Transform)

- not FFT
- 10 times faster than software implementation

## TDSE (Time-Dependent Schrodinger Equation)

- Trotter-Suzuki Method
- 100x100 lattice
- Diffraction of a wave packet through a hole
- 200+ times faster than software implementation
- reference: De Raedt, Hans. "Computer simulation of quantum phenomena in nanoscale devices." Annual Reviews of Computational Physics IV (1996): 107-146.

## 注意

- HLS pragmas are not in the source codes but in `directives.tcl, which is more convenient in IDE for comparison between different solutions.
- Based on xc7z010clg400-1, not xc7z020clg484-1 in PYNQ-Z2.
