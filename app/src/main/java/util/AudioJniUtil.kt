package util

import util.SrcParams

class AudioJniUtil {

    var srcPtr: Long = 0L

    external fun getVersion(string: String, length: Int): Int

    external fun srcInit(srcParams: SrcParams): Int

    external fun srcProcess(srcFilePath: String, dstFilePath: String): Int

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }

}