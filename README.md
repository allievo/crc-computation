CRC COMPUTATION
=============

crc/ directory:
the project 'crc_computation' compares the traditional solution (256 items lookup table) with a faster solution (that requires a 65536 items lookup table);
the faster solution was tested with a DSP and the time required to process a buffer of data was decreased by 40 percent;
the algorithm requires that the buffer size must be an even value;
