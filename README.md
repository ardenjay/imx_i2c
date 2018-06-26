# imx_i2c

A tiny program for demonstration access i2c from Android apk

To grant the permission for /dev/i2c-0,

1. disable SELinux
2. change the i2c-0 permission by adding it below on the system/core/rootdir/ueventd.rc

		diff --git a/rootdir/ueventd.rc b/rootdir/ueventd.rc
		index 6ef491c..66f8a4e 100644
		--- a/rootdir/ueventd.rc
		+++ b/rootdir/ueventd.rc
		@@ -19,6 +19,7 @@ subsystem adf
		 /dev/hw_random            0440   root       system
		 /dev/ashmem               0666   root       root
		 /dev/binder               0666   root       root
		+/dev/i2c-0                0666   root       root
