# Kernel Module

> ...

## Build

```bash
make
sudo insmod hello.ko
dmesg | tail -n 10  # Check kernel log
sudo rmmod hello     # Remove module
```

## Module Signing

> ...

## References

- https://github.com/NVIDIA/open-gpu-kernel-modules/discussions/542