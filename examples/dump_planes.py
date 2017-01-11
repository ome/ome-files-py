#!/usr/bin/env python

"""\
Open an OME-TIFF file and dump each plane to an individual TIFF
file. Works only on non-RGB data at the moment.
"""

import sys
import argparse
from contextlib import closing

from libtiff import TIFF
import numpy as np

import ome_files


def dump(ome_tiff_fn):
    reader = ome_files.OMETIFFReader()
    reader.set_id(ome_tiff_fn)
    img_count = reader.get_image_count()
    print "image count: %d" % img_count
    for i in xrange(img_count):
        raw = reader.open_bytes(i)
        H, W = reader.get_size_y(), reader.get_size_x()
        dtype = reader.get_pixel_type()
        pixels = np.fromstring(raw, dtype=dtype).reshape((H, W))
        out_fn = "plane_%d.tiff" % i
        print "writing %s" % out_fn
        with closing(TIFF.open(out_fn, mode="w")) as fo:
            fo.write_image(pixels)
    reader.close()


def make_parser():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('ome_tiff_fn', metavar="OME_TIFF_FILE")
    return parser


def main(argv):
    parser = make_parser()
    args = parser.parse_args(argv[1:])
    dump(args.ome_tiff_fn)


if __name__ == "__main__":
    main(sys.argv)
