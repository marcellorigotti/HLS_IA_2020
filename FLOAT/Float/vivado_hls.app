<project xmlns="com.autoesl.autopilot.project" top="lenet_cnn" name="Float">
    <includePaths/>
    <libraryPaths/>
    <Simulation argv="">
        <SimFlow name="csim" ldflags="-lhdf5_serial -lm" clean="true" csimMode="0" lastCsimMode="0"/>
    </Simulation>
    <files xmlns="">
        <file name="../../mnist" sc="0" tb="1" cflags="  -Wno-unknown-pragmas"/>
        <file name="../../lenet_cnn_float.c" sc="0" tb="1" cflags=" -l/usr/include/hdf5/serial/.-O3 -Wno-unknown-pragmas"/>
        <file name="utils.c" sc="0" tb="false" cflags="-l/usr/include/hdf5/serial/.-O3"/>
        <file name="pool.c" sc="0" tb="false" cflags=""/>
        <file name="lenet_weights.hdf5" sc="0" tb="false" cflags=""/>
        <file name="lenet_cnn_float.c" sc="0" tb="false" cflags=""/>
        <file name="fc.c" sc="0" tb="false" cflags=""/>
        <file name="conv.c" sc="0" tb="false" cflags=""/>
    </files>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
    </solutions>
</project>

