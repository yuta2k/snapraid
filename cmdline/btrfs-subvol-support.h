#if !defined(_BTRFS_SUBVOL_SUPPORT_H) && defined(BTRFS_SUBVOL_SUPPORT)
#define _BTRFS_SUBVOL_SUPPORT_H

#include <fcntl.h>
#include <stddef.h>
#include <sys/ioctl.h>
#include <linux/btrfs.h>
#include <uuid/uuid.h>

/**
 * Get the UUID of a subvolume from the path of the subvolume or directory under it.
 * "uuid" parameter is must be greater than or equal to UUID_STR_LEN (37 bytes).
 */
int btrfs_subvol_uuid(const char* path, char* uuid, size_t uuid_size) {
	if (uuid_size < UUID_STR_LEN) {
		log_fatal("The length of the UUID must be at least %d, but is %zu.\n", UUID_STR_LEN, uuid_size);
		exit(EXIT_FAILURE);
	}

	int fd = open(path, O_RDONLY);
	if (fd == -1) {
		return -1;
	}

	struct btrfs_ioctl_get_subvol_info_args info;
	int ioctl_ret = ioctl(fd, BTRFS_IOC_GET_SUBVOL_INFO, &info);
	if (ioctl_ret == -1) {
		return -1;
	}

	uuid_unparse(info.uuid, uuid);
	return 1;
}

#endif /* !defined(_BTRFS_SUBVOL_SUPPORT_H) && BTRFS_SUBVOL_SUPPORT */
