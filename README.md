# PatternSpace

C++ prototype for garment pattern generation using linear algebra and computational geometry.

PatternSpace begins with a fitted sleeveless bodice. Measurements are converted into geometric landmarks, pattern pieces are represented as 2D point sets, affine transformations modify their geometry, and cubic Bezier curves model curved boundaries such as necklines and armholes. The program exports the generated front and back pieces as SVG.

## Mathematics

A pattern landmark is a vector p = (x, y). Transformations use p' = Ap + b, where A is a 2x2 matrix and b is a translation vector. Curves use cubic Bezier interpolation. A simple feature-vector model compares garment/pattern characteristics with Euclidean distance as a nearest-neighbor baseline.

## Prototype features

- Measurement-driven front and back bodice generation
- 2D vectors and 2x2 matrices
- Scaling, rotation, and translation
- Cubic Bezier curves
- Polyline and curve-length estimation
- Pattern feature vectors
- Nearest-neighbor pattern matching
- SVG pattern export

## Roadmap

The next stage is image analysis: extracting normalized silhouette and landmark features from front/back garment photographs. Those features can select and transform a base pattern. A later version can use PCA/SVD to learn a low-dimensional pattern shape space.

## Build

```bash
cmake -S . -B build
cmake --build build
./build/patternspace
```

The program writes `patternspace_output.svg`.

## Scope

PatternSpace is an educational computational-geometry prototype, not a production pattern-drafting system. Generated pieces should be validated before being used to cut fabric.
