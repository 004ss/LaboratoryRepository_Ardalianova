# LaboratoryRepository_Ardalianova

Software Engineering labs, NTU "KhPI", group KN-226E.
Author: Ardalianova Sofiia (variant 1).

## About
Console C++ application **Function Calculator**. It calculates the function y for every x
from the range (a, b) with the step h:

- y = Σ (i = 2..n) (i − 3 + x)² − 5x, if x < 0
- y = Σ (i = 0..n) Π (j = 1..n − 1) (i + j) / (2(1 + x)²), if x ≥ 0

The results are shown on the screen and saved to `results.txt`.

## Files
- `LabWork2_ArdalianovaSofiia.cpp` – source code of the program
- `SRS_Ardalianova.docx` – Software Requirements Specification

## How to run
Open the code in Visual Studio, build it and run (Ctrl + F5).
Enter a, b, h and n (a < b, h > 0, n is an integer, n ≥ 2).
