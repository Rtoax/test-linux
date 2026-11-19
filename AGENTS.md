# AGENTS.md

This file provides context for AI agents when working on the test-linux
codebase.

More to see the Documentation directory.

## Project overview

The **Test Linux** project is the Linux test project.

The **Test Linux** repository contains **GNU/Linux** related test case codes,
scripts and knowledge points, as well as operating system related content.

`rtoax/test-linux` is a **broad, hands-on collection of experiments, minimal examples, and notes for testing and exploring GNU/Linux technologies**. Its self-description is simply "Try and test everything on GNU/Linux". Rather than being a single product, it functions more like a living **technical field notebook**—the author tests a concept, captures the smallest runnable example, and files it away under a clearly named directory.

### 📂 Content organization: a topic-by-topic "toolbox"

The repository is organized primarily by **technology area**, so you can navigate directly to the subject you care about:

- **Core Linux & C**: `c`, `algorithm`, `compiler`, `libs`
- **Kernel observation & control**: `bpf`, `cgroup`, `audit`, `mm` (memory management), `module` (kernel modules)
- **Architecture & platform**: `arch` (e.g., RISC-V/QEMU setup records)
- **Networking & namespaces**: `network`, `namespace`
- **AI & language bindings**: `ai`, `lua`, `perl`, `php`, `python`
- **Documentation**: a dedicated `Documentation` folder for guides and quick-starts

Each directory typically contains test code, configuration snippets, and sometimes the author's own kernel modules or user-space programs—some drawn from kernel `samples/`, some from open-source projects, and some written specifically for the test.

### 🚀 Getting started

The Gitee mirror points readers to the repository's documentation, specifically a **quick-start guide** located at `Documentation/devel/quickstart.rst`. If you want to build or run any of the experiments, that is the recommended entry point.

### ⚖️ License: not a single blanket license

The `LICENSE` entry in the repository explicitly lists **multiple licenses**: BSD, CC-BY-SA, GPL, LGPL, and Mulan. This means you must check the header of individual files or subdirectories to confirm which terms apply to the specific code you intend to reuse.



### 💡 Who it is useful for

- **Linux systems/kernel learners**: It works as a **topic-indexed bank of minimal examples**—if you want to quickly see a working demo of a cgroup feature, a BPF program, or a kernel module, scanning the relevant folder is often faster than starting from scratch.
- **People working across architectures**: The `arch` directory includes notes on setting up cross-architecture environments (e.g., RISC-V with QEMU and toolchains), which can save configuration time.
- Because the repository is actively maintained (with commits touching areas like Debian documentation, RISC-V, and BPF as of late 2026), it also reflects what the author is currently exploring.

In short, `test-linux` is a **breadth-first, verification-oriented reference**—valuable not for delivering a finished product, but for aggregating many **small, runnable Linux experiments** in one place.
