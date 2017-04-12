# Release Notes

# v0.1.0

This is the initial release which mixes gnuplot based graphing with
matplotlib graphing.

**Limitations**

* Currently the main gnuplot-based plotting engine is not fully because
there are data from multiple nodes mixed into the .csv files.

**Performance**

* Rendering 2 boxes using matplotlib and pandas from 2015-01-01 to
    2016-12-06 takes approx 8 minutes.. this should probably be fixed
    in the future since it's quite a while for two nodes
