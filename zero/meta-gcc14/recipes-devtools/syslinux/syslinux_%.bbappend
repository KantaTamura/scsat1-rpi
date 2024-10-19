FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI += "file://0001-Fix-build-with-GCC-14.patch"

do_configure:prepend() {
    rm -f ${S}/core/fs/ext2/ext2_fs.h
    rm -f ${S}/libinstaller/ext2fs/ext2_fs.h
}
