package util

import util.SrcParams

class AudioJniUtil {

    var srcPtr: Long = 0L
    var nsPtr: Long = 0L
    var agcPtr: Long = 0L

    external fun srcInit(srcParams: SrcParams): Int

    external fun srcProcess(srcFilePath: String, dstFilePath: String): Int

    external fun nsInit(nsParams: NsParams):Int

    external fun nsProcess(srcFilePath: String, dstFilePath: String):Int

    external fun agcInit(agcParams: AgcParams):Int

    external fun agcProcess(srcFilePath: String, dstFilePath: String):Int

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }

}