# RayBorn: Impact of Optimization Techniques on C++ Ray Tracing Performance


**RayBorn Team –  Kader Bakayoko, Adam Drici, Elyes Ouramdane**  
Hetic Master CTO & Tech Lead 2026


## Abstract

Physically-based ray tracing produces high-quality images at a significant material cost. In the context of film
production, a single 90-minute feature may require rendering more than 100,000 high-resolution frames, making
performance a critical concern. In this work, we present *RayBorn*, a modular C++ ray tracer, and we systematically
evaluate the impact of several CPU-based optimization techniques on image generation time. We compare a baseline
implementation to combinations of micro-optimizations in vector math, multithreading, and spatial acceleration
(Bounding Volume Hierarchies, BVH) across two representative scenes: (i) a simple scene with few objects and a high
sampling per pixel rate, and (ii) a complex scene with about 500 spheres and a lower sampling rate. Our results show that the
optimal optimization strategy strongly depends on workload: in simple scenes, multithreading and per-ray math
optimizations dominate, whereas in complex scenes, spatial acceleration becomes the key factor, with up to 38× speedup
over the baseline. We discuss these findings in the light of classical advice on premature optimization and outline
directions for future work, including octrees, improved sampling, and GPU-based ray tracing.

## 1. Introduction

Ray tracing is a fundamental technique in physically-based rendering, capable of producing highly realistic images
by simulating light transport through a 3D scene. However, the computational cost of tracing millions to billions
of rays per frame remains a major bottleneck, particularly for film production, where hundreds of thousands of frames
must be rendered under strict time and budget constraints.

In the scenario motivating this work, the global 3D rendering industry of 2035 suffers from slow, proprietary and
unreliable tools, and a Los Angeles–based film studio needs a new reliable, efficient and maintainable rendering engine
written in C++. As a response, we designed and implemented *RayBorn*, a ray tracer built from first principles, and
we focused on measuring the impact of different optimization strategies on rendering performance.

Our goal is to answer a more engineering-oriented question:
*Given a reasonably realistic ray tracer, which optimization techniques provide the best return on investment,
and under which workloads?* To this end, we compare micro-optimizations in the math kernel, multithreading,
and spatial acceleration (BVH), on two scenes with very different characteristics.

## 2. Materials and Methods

### 2.1. RayBorn architecture

RayBorn is implemented in modern C++ and follows a modular architecture. The main components are:

- **Math & Geometry**: vector utilities (e.g., `vec3`), random sampling, and geometric primitive definitions  
- **Scene Representation**: primitive classes for spheres, planes, triangles and cubes, as well as a generic
  `hittable_list` container  
- **Acceleration Structures**: a Bounding Volume Hierarchy (`bvh_node`) built over scene primitives  
- **Rendering Core**: a recursive path tracer that supports Lambertian and metallic materials with up to 5 bounces  
- **Camera and Image Output**: a configurable camera with perspective projection and PNG image export  

The ray tracer supports anti-aliasing via multiple samples per pixel (spp).

### 2.2. Test scenes

We evaluate RayBorn on two scenes designed to stress different parts of the rendering pipeline.

**Scene A – Few objects, high sampling.**  
This scene contains a ground plane, three main spheres (Lambertian and metal), a cube, and large background geometry.
The camera is configured with a 16:9 aspect ratio, resolution 1920×1080, 500 samples per pixel and a maximum path
depth of 5. This configuration yields billions of rays when accounting for all samples and bounces, and is designed to
be dominated by per-ray operations such as sampling and shading.

**Scene B – Many objects, lower sampling.**  
The second scene reuses the same base layout but adds approximately 500 spheres arranged in several clusters (dense,
medium, sparse and background), combining Lambertian and metal materials. Here, the camera uses 100 samples per pixel
and a maximum depth of 5. This configuration is intended to be dominated by ray–geometry intersection and spatial
traversal costs.

#### Scene A
<img width="1920" height="1080" alt="scene_A" src="https://github.com/user-attachments/assets/8346c1c5-fb1d-4c4e-9f7b-38e9acf4b4b5" />

#### Scene B
![scene_B](https://github.com/user-attachments/assets/9f4130ac-46d5-4352-ab72-c039efbee24f)


### 2.3. Optimization scenarios

We measure eight optimization scenarios for each scene:

1. **Baseline**: single-threaded execution, no BVH, naive vector operations (multiple divisions during normalization).  
2. **Minor Optimizations**: single-threaded, no BVH, but with micro-optimizations in the math kernel (e.g., replacing
   three divisions by one division plus three multiplications, and implementing a more efficient `unit_vector`).  
3. **BVH Only**: single-threaded rendering with BVH acceleration, naive vector math.  
4. **BVH + Minor**: BVH plus math micro-optimizations, single-threaded.  
5. **Multithreading Only**: multithreaded rendering without BVH, naive vector math.  
6. **MT + Minor**: multithreading plus math micro-optimizations, no BVH.  
7. **BVH + MT**: BVH acceleration and multithreaded rendering, naive vector math.  
8. **All Optimizations**: BVH + multithreading + math micro-optimizations.  

For each scenario, we render a 1920×1080 image and measure the total render time in seconds. Each configuration is
run 10 times to estimate mean and standard deviation.

For completeness, we also tested a **Debug** build configuration (no compiler optimizations, additional runtime checks).
On our hardware, all 10 runs for this scenario failed to complete within our time budget and were recorded as `TIMEOUT`
in the raw data. As a consequence, the Debug scenario is excluded from the aggregated statistics and plots presented
in Section 3.

### 2.4. Hardware and execution environment

All experiments were run on a laptop equipped with an AMD Ryzen™ 7 PRO 7730U processor (8 cores / 16 hardware threads,
base frequency 2.0 GHz, boost up to 4.5 GHz), 64 GB DDR4-3200 MHz RAM (2 × 32 GB SODIMM), and a 1 TB M.2 PCIe Gen4 SSD
(Opal). The operating system was Ubuntu Linux (multilingual configuration). For multithreaded configurations, RayBorn
uses up to 16 threads, matching the number of hardware threads exposed by the CPU.

## 3. Results

### 3.1. Scene A – Few objects, 500 spp

The baseline configuration for Scene A takes approximately 376 seconds per frame. Minor Optimizations alone have almost
no effect (~378 s), while BVH Only and BVH + Minor reach around 267–262 seconds (1.4× speedup). Multithreading Only
reduces the render time to approximately 216 seconds (1.7× speedup). The best configurations are BVH + MT (~72.6 s,
5.2× speedup) and All Optimizations (~65.5 s, 5.7× speedup).

<img width="1600" height="800" alt="rayborn_scene1_mean_time (2)" src="https://github.com/user-attachments/assets/d1d57c16-fb04-4fcc-89c2-cdc0355ecc4d" />
<img width="1600" height="800" alt="rayborn_scene1_speedup (1)" src="https://github.com/user-attachments/assets/f500487d-4c93-494f-b7b3-00a52cbfce7e" />


### 3.2. Scene B – Many objects, 100 spp

Scene B contains approximately 500 spheres and is designed to be dominated by ray–geometry intersection costs.
In this setting, the baseline render time is about 1060 seconds (~17.7 minutes). Minor Optimizations alone again
provide negligible improvement (~1044 s, 1.02× speedup). In contrast, BVH Only and BVH + Minor both reach around
131–132 seconds, corresponding to an 8× speedup, confirming that spatial acceleration is crucial when many objects
are present. Multithreading Only yields a 4.6× speedup (230 s). Combining BVH and multithreading (BVH + MT) reduces
render time to approximately 30.9 seconds (34× speedup), and the All Optimizations scenario further improves this to
27.9 seconds (~38× speedup).

<img width="1600" height="800" alt="rayborn_scene2_mean_time (1)" src="https://github.com/user-attachments/assets/c4a89422-7fc1-475c-b05a-e73c7f9b5ac0" />
<img width="1600" height="800" alt="rayborn_scene2_speedup (1)" src="https://github.com/user-attachments/assets/50bd18cb-1e96-40fd-b91e-58dc600a8d2d" />



## 4. Discussion

Our experiments highlight that the impact of an optimization technique on ray tracing performance is strongly
workload-dependent. In Scene A (few objects, many samples), the dominant cost comes from per-ray operations:
random sampling for Lambertian materials, vector normalization, and shading. In this regime, BVH provides only
a modest improvement, while multithreading and micro-optimizations in the math kernel (when combined) lead to
substantial gains.

In Scene B (many objects, fewer samples), performance is clearly dominated by ray–object intersection and spatial
traversal. Here, BVH acceleration becomes the pivotal optimization, providing an 8× speedup even in single-threaded
mode. Multithreading amplifies these gains, and the combination of BVH + MT + micro-optimizations reaches a 38×
speedup over the baseline, reducing render time from ~1060 seconds to ~28 seconds per frame.

An important observation is that micro-optimizations alone rarely justify their engineering complexity: they had almost
no measurable impact in isolation on either scene. Their true value appears only after the main architectural
bottlenecks (lack of multithreading, absence of spatial acceleration) have been addressed. This suggests a pragmatic
workflow: first implement a correct and maintainable baseline, then add architectural optimizations such as
multithreading and BVH, and only finally optimize the hot inner loops where profiling shows clear bottlenecks.

### 4.1. Linking performance back to the code

The performance behavior observed in our experiments can be directly explained by the structure of the RayBorn code.

For each pixel, the renderer loops over `samples_per_pixel` and calls a recursive `ray_color` function up to
`max_depth` bounces. For Lambertian materials, each bounce generates one or more random directions (e.g. in a unit
sphere or hemisphere) and performs several vector operations (normalization, dot products, component-wise products).
In other words, the total cost is roughly proportional to:

> #pixels × samples_per_pixel × expected_bounces ×  
> (cost of rrandom numbers calls + cost of vec3 operations + cost of ray–scene intersection).

In Scene A, the scene contains only a handful of primitives (plane, a few spheres, one cube). The cost of looping
over all objects for each ray is therefore relatively small. What dominates is the per-ray work: random sampling,
vector math, recursion and shading. Because we use 500 samples per pixel, the renderer generates billions of rays,
and each ray triggers several calls to the random number generator and vector normalization routines. This explains
why multithreading and micro-optimizations in `vec3` are very effective when combined, whereas BVH brings only
a modest speedup: with so few objects, the overhead of BVH traversal is comparable to simply iterating over the list
of primitives.

In Scene B, the situation is completely different. The scene contains approximately 500 spheres on top of the base
geometry, so each ray in the Baseline configuration must test intersections against hundreds of primitives. In this
regime, the cost of the random sampling and vector math is still present, but it is dwarfed by the cost of repeatedly
calling `hit()` on every object in the scene. Introducing a BVH replaces this O(N) loop over ~500 primitives by a
hierarchical traversal where most subtrees are quickly rejected using cheap AABB tests, and only a small number of
primitives are actually intersected. This reduces the number of ray–primitive intersection tests by roughly an order
of magnitude, which matches the ~8× speedup observed in our measurements for BVH-only configurations.

### 4.2. Role of multithreading and interaction with sampling

Ray tracing is an embarrassingly parallel problem at the pixel level: each pixel can be rendered independently.
In our implementation, multithreading simply distributes scanlines across the 16 hardware threads of the AMD Ryzen™ 7
PRO 7730U used for the experiments. The higher the number of samples per pixel, the more compute work per pixel, and
the better the CPU can be saturated by multiple threads.

In Scene A, with 500 spp and relatively cheap ray–scene intersections, the workload is dominated by per-ray sampling
and shading, which parallelize extremely well. This explains why the Multithreading Only and BVH + MT configurations
achieve large speedups compared to the single-threaded baseline. In Scene B, multithreading still brings a substantial
benefit, but the scaling is also influenced by memory hierarchy effects (a larger BVH, more cache misses) and by the
cost of traversing a deeper acceleration structure.

An important observation is that micro-optimizations in the math kernel (such as reducing the number of divisions in
`unit_vector`) have almost no visible effect when used alone, but become meaningful once the main architectural
bottlenecks (lack of BVH, lack of multithreading) have been addressed. At that point, the inner loops of the renderer
are “hot” enough that saving a few cycles per operation translates into measurable gains at the frame level.

## 5. Conclusion and Future Work

We presented RayBorn, a C++ ray tracer designed as a testbed to study the impact of several CPU optimization strategies
on physically-based image generation. On two complementary scenes, we showed that multithreading, spatial acceleration
and micro-optimizations interact in non-trivial ways, and that their effectiveness depends heavily on scene complexity
and sampling regime. In particular, BVH acceleration is essential for complex scenes with many objects, while math
micro-optimizations only deliver meaningful benefits when combined with multithreading and BVH.

Future work will focus on several directions. First, we plan to implement and compare alternative spatial data
structures such as octrees, especially for highly clustered or non-uniform scenes. Second, we aim to improve sampling
for diffuse BRDFs via better importance sampling and variance reduction techniques, with the goal of reducing the
required samples per pixel for a given noise level. Finally, we envision porting the core ray traversal and shading
loops to GPU, leveraging modern hardware ray tracing capabilities to explore real-time or near real-time applications.

## References

[1] P. Shirley – "Ray Tracing in One Weekend", 2016.  
[2] P. Shirley – "Ray Tracing: The Next Week", 2016.  
[3] P. Shirley – "Ray Tracing: The Rest of Your Life", 2016.  
[4] J. Buck – "The Ray Tracer Challenge", Pragmatic Bookshelf, 2019.  
[5] M. Pharr, W. Jakob, G. Humphreys – "Physically Based Rendering: From Theory to Implementation", 3rd ed., 2016.  
[6] J. Bikker – "How to build a BVH – Part 1: Basics", 2022.  
[7] A. Hotwani – "Ray Tracing Meshes", 2020.  
[8] The Cherno – Ray tracing and C++ video series (YouTube).  
Elyes Ouramdane**  
Hetic Master CTO & Tech Lead 2026


## Abstract

Physically-based ray tracing produces high-quality images at a significant computational cost. In the context of film
production, a single 90-minute feature may require rendering more than 100,000 high-resolution frames, making
performance a critical concern. In this work, we present *RayBorn*, a modular C++ ray tracer, and we systematically
evaluate the impact of several CPU-based optimization techniques on image generation time. We compare a baseline
implementation to combinations of micro-optimizations in vector math, multithreading, and spatial acceleration
(Bounding Volume Hierarchies, BVH) across two representative scenes: (i) a simple scene with few objects and a high
sampling rate, and (ii) a complex scene with about 500 spheres and a lower sampling rate. Our results show that the
optimal optimization strategy strongly depends on workload: in simple scenes, multithreading and per-ray math
optimizations dominate, whereas in complex scenes, spatial acceleration becomes the key factor, with up to 38× speedup
over the baseline. We discuss these findings in the light of classical advice on premature optimization and outline
directions for future work, including octrees, improved BRDF sampling, and GPU-based ray tracing.


# Appendix – Detailed Numeric Results

## A.1 Scene A – Per-scenario statistics (few objects, 500 spp)

| Scenario | Mean time (s) | Std dev (s) | Runs | Speedup vs Baseline |
|----------|----------------|-------------|------|----------------------|
| Minor Optimizations | 378.346 | 0.969 | 10 | 0.99 |
| Baseline | 376.199 | 1.670 | 10 | 1.00 |
| BVH Only | 267.086 | 8.418 | 10 | 1.41 |
| BVH + Minor | 262.413 | 11.920 | 10 | 1.43 |
| Multithreading Only | 216.429 | 0.856 | 10 | 1.74 |
| MT + Minor | 75.291 | 1.958 | 10 | 5.00 |
| BVH + MT | 72.604 | 2.503 | 10 | 5.18 |
| All Optimizations | 65.488 | 2.056 | 10 | 5.74 |

## A.2 Scene B – Per-scenario statistics (500 spheres, 100 spp)

| Scenario | Mean time (s) | Std dev (s) | Runs | Speedup vs Baseline |
|----------|----------------|-------------|------|----------------------|
| Baseline | 1060.434 | 13.263 | 10 | 1.00 |
| Minor Optimizations | 1044.447 | 14.811 | 10 | 1.02 |
| MT + Minor | 256.581 | 6.062 | 10 | 4.13 |
| Multithreading Only | 230.182 | 5.051 | 10 | 4.61 |
| BVH Only | 131.754 | 2.575 | 10 | 8.05 |
| BVH + Minor | 131.589 | 1.100 | 10 | 8.06 |
| BVH + MT | 30.857 | 0.467 | 10 | 34.37 |
| All Optimizations | 27.926 | 0.332 | 10 | 37.97 |

## A.3 Scene A – Per-run render times

| Scenario | Run | Time (s) |
|----------|-----|----------|
| All Optimizations | 1 | 67.093 |
| All Optimizations | 2 | 62.844 |
| All Optimizations | 3 | 68.138 |
| All Optimizations | 4 | 65.394 |
| All Optimizations | 5 | 63.567 |
| All Optimizations | 6 | 64.540 |
| All Optimizations | 7 | 63.076 |
| All Optimizations | 8 | 64.740 |
| All Optimizations | 9 | 68.137 |
| All Optimizations | 10 | 67.347 |
| BVH + MT | 1 | 76.779 |
| BVH + MT | 2 | 73.861 |
| BVH + MT | 3 | 72.142 |
| BVH + MT | 4 | 69.343 |
| BVH + MT | 5 | 72.638 |
| BVH + MT | 6 | 73.579 |
| BVH + MT | 7 | 68.612 |
| BVH + MT | 8 | 75.325 |
| BVH + MT | 9 | 71.117 |
| BVH + MT | 10 | 72.646 |
| BVH + Minor | 1 | 252.234 |
| BVH + Minor | 2 | 273.800 |
| BVH + Minor | 3 | 268.346 |
| BVH + Minor | 4 | 273.800 |
| BVH + Minor | 5 | 247.724 |
| BVH + Minor | 6 | 270.841 |
| BVH + Minor | 7 | 273.800 |
| BVH + Minor | 8 | 247.724 |
| BVH + Minor | 9 | 247.724 |
| BVH + Minor | 10 | 268.131 |
| BVH Only | 1 | 270.887 |
| BVH Only | 2 | 271.183 |
| BVH Only | 3 | 251.426 |
| BVH Only | 4 | 263.832 |
| BVH Only | 5 | 254.071 |
| BVH Only | 6 | 273.746 |
| BVH Only | 7 | 272.475 |
| BVH Only | 8 | 268.583 |
| BVH Only | 9 | 267.299 |
| BVH Only | 10 | 277.360 |
| Baseline | 1 | 377.420 |
| Baseline | 2 | 376.865 |
| Baseline | 3 | 377.277 |
| Baseline | 4 | 379.209 |
| Baseline | 5 | 376.412 |
| Baseline | 6 | 373.914 |
| Baseline | 7 | 375.458 |
| Baseline | 8 | 376.070 |
| Baseline | 9 | 375.806 |
| Baseline | 10 | 373.561 |
| MT + Minor | 1 | 75.244 |
| MT + Minor | 2 | 72.031 |
| MT + Minor | 3 | 74.872 |
| MT + Minor | 4 | 76.200 |
| MT + Minor | 5 | 77.584 |
| MT + Minor | 6 | 73.202 |
| MT + Minor | 7 | 75.065 |
| MT + Minor | 8 | 76.294 |
| MT + Minor | 9 | 73.917 |
| MT + Minor | 10 | 78.502 |
| Minor Optimizations | 1 | 379.146 |
| Minor Optimizations | 2 | 377.194 |
| Minor Optimizations | 3 | 376.765 |
| Minor Optimizations | 4 | 379.147 |
| Minor Optimizations | 5 | 378.256 |
| Minor Optimizations | 6 | 379.850 |
| Minor Optimizations | 7 | 379.037 |
| Minor Optimizations | 8 | 378.359 |
| Minor Optimizations | 9 | 378.076 |
| Minor Optimizations | 10 | 377.626 |
| Multithreading Only | 1 | 216.592 |
| Multithreading Only | 2 | 216.417 |
| Multithreading Only | 3 | 217.556 |
| Multithreading Only | 4 | 216.946 |
| Multithreading Only | 5 | 217.735 |
| Multithreading Only | 6 | 216.088 |
| Multithreading Only | 7 | 215.146 |
| Multithreading Only | 8 | 216.054 |
| Multithreading Only | 9 | 215.242 |
| Multithreading Only | 10 | 216.518 |

## A.4 Scene B – Per-run render times

| Scenario | Run | Time (s) |
|----------|-----|----------|
| All Optimizations | 1 | 28.309 |
| All Optimizations | 2 | 27.751 |
| All Optimizations | 3 | 27.792 |
| All Optimizations | 4 | 28.182 |
| All Optimizations | 5 | 28.400 |
| All Optimizations | 6 | 27.544 |
| All Optimizations | 7 | 27.626 |
| All Optimizations | 8 | 27.544 |
| All Optimizations | 9 | 27.843 |
| All Optimizations | 10 | 28.271 |
| BVH + MT | 1 | 30.748 |
| BVH + MT | 2 | 29.968 |
| BVH + MT | 3 | 31.247 |
| BVH + MT | 4 | 31.337 |
| BVH + MT | 5 | 31.337 |
| BVH + MT | 6 | 30.422 |
| BVH + MT | 7 | 31.310 |
| BVH + MT | 8 | 30.473 |
| BVH + MT | 9 | 30.932 |
| BVH + MT | 10 | 30.794 |
| BVH + Minor | 1 | 132.153 |
| BVH + Minor | 2 | 132.689 |
| BVH + Minor | 3 | 131.216 |
| BVH + Minor | 4 | 130.767 |
| BVH + Minor | 5 | 130.054 |
| BVH + Minor | 6 | 132.689 |
| BVH + Minor | 7 | 130.663 |
| BVH + Minor | 8 | 130.283 |
| BVH + Minor | 9 | 132.689 |
| BVH + Minor | 10 | 132.689 |
| BVH Only | 1 | 134.569 |
| BVH Only | 2 | 129.890 |
| BVH Only | 3 | 131.582 |
| BVH Only | 4 | 128.604 |
| BVH Only | 5 | 131.704 |
| BVH Only | 6 | 129.215 |
| BVH Only | 7 | 135.970 |
| BVH Only | 8 | 134.568 |
| BVH Only | 9 | 129.300 |
| BVH Only | 10 | 132.141 |
| Baseline | 1 | 1066.667 |
| Baseline | 2 | 1052.369 |
| Baseline | 3 | 1053.224 |
| Baseline | 4 | 1047.446 |
| Baseline | 5 | 1052.806 |
| Baseline | 6 | 1078.373 |
| Baseline | 7 | 1045.557 |
| Baseline | 8 | 1082.724 |
| Baseline | 9 | 1071.282 |
| Baseline | 10 | 1053.892 |
| MT + Minor | 1 | 249.863 |
| MT + Minor | 2 | 261.831 |
| MT + Minor | 3 | 259.572 |
| MT + Minor | 4 | 262.436 |
| MT + Minor | 5 | 248.854 |
| MT + Minor | 6 | 261.034 |
| MT + Minor | 7 | 254.046 |
| MT + Minor | 8 | 259.094 |
| MT + Minor | 9 | 246.985 |
| MT + Minor | 10 | 262.098 |
| Minor Optimizations | 1 | 1030.170 |
| Minor Optimizations | 2 | 1030.170 |
| Minor Optimizations | 3 | 1059.622 |
| Minor Optimizations | 4 | 1030.170 |
| Minor Optimizations | 5 | 1058.050 |
| Minor Optimizations | 6 | 1066.729 |
| Minor Optimizations | 7 | 1046.589 |
| Minor Optimizations | 8 | 1057.438 |
| Minor Optimizations | 9 | 1031.218 |
| Minor Optimizations | 10 | 1034.310 |
| Multithreading Only | 1 | 228.788 |
| Multithreading Only | 2 | 223.953 |
| Multithreading Only | 3 | 223.851 |
| Multithreading Only | 4 | 236.114 |
| Multithreading Only | 5 | 234.547 |
| Multithreading Only | 6 | 226.397 |
| Multithreading Only | 7 | 235.194 |
| Multithreading Only | 8 | 225.804 |
| Multithreading Only | 9 | 236.114 |
| Multithreading Only | 10 | 231.057 |

## A.5 Debug configuration – TIMEOUTs

The `Debug` build never completed within the allowed time budget in either scene. All runs were recorded as `TIMEOUT`.

### Scene A – Debug runs

| Run | Status |
|-----|--------|
| 1 | TIMEOUT |
| 2 | TIMEOUT |
| 3 | TIMEOUT |
| 4 | TIMEOUT |
| 5 | TIMEOUT |
| 6 | TIMEOUT |
| 7 | TIMEOUT |
| 8 | TIMEOUT |
| 9 | TIMEOUT |
| 10 | TIMEOUT |

### Scene B – Debug runs

| Run | Status |
|-----|--------|
| 1 | TIMEOUT |
| 2 | TIMEOUT |
| 3 | TIMEOUT |
| 4 | TIMEOUT |
| 5 | TIMEOUT |
| 6 | TIMEOUT |
| 7 | TIMEOUT |
| 8 | TIMEOUT |
| 9 | TIMEOUT |
| 10 | TIMEOUT |

