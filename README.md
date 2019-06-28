# Kernel

## CMD PROCESS

**make** Building the project and the iso: k.iso

**qemu-system-i386 -cdrom k.iso [ -enable-kvm ]** Run the kernel with qemu

To debug, add "-s -S" to qemu option, then run:
**gdb k/k**
