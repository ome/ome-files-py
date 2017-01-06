import os
from contextlib import closing

from libtiff import TIFF
import numpy as np

import ome_files


THIS_DIR = os.path.dirname(os.path.abspath(__file__))
IMG_PATH = os.path.join(
    THIS_DIR, os.pardir, "test", "data", "multi-channel-4D-series.ome.tif"
)

# TODO: make the following info available via the API
PIXEL_TYPE = np.int8
H, W = 167, 439

reader = ome_files.OMETIFFReader()
reader.set_id(IMG_PATH)
img_count = reader.get_image_count()
print "image count: %d" % img_count
for i in xrange(img_count):
    raw = reader.open_bytes(i)
    pixels = np.fromstring(raw, dtype=PIXEL_TYPE).reshape((H, W))
    out_fn = "plane_%d.tiff" % i
    print "writing %s" % out_fn
    with closing(TIFF.open(out_fn, mode="w")) as fo:
        fo.write_image(pixels)
reader.close()
