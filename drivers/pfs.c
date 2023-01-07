//
// pos file system
//
#pragma once
#include "ata.c"
#include "../misc/defs.c"
#include "../misc/bitflags.c"

// file header
// 0 - 100: filename (truncated if neccicary)
// 101: file permissions
// 102-105 (dword): file size (max filesize is slightly less than 4.3gb,
//                  files should never get this big considering memory 
//                  on a 32 bit system is limited to 4gb)
// 105-150: owner (truncated if neccicary)
// 151-154: "PFS", followed by null
// 155: version, this driver is version 1


u8 PFSreserveFileSpace() {

}

u8 PFSreadFile() {

}

u8 PFSwriteFile() {

}