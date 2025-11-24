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
