package util

import util.bean.AgcParams
import util.bean.NsParams
import util.bean.SrcParams


/**
 * communicate with audio so file
 */
class AudioJniUtil {
    /**
     * src(sample rate change) pointer in c
     */
    var srcPtr: Long = 0L

    /**
     * ns(noise suppress) pointer in c
     */
    var nsPtr: Long = 0L

    /**
     * agc(Automatic Gain Control) pointer in c
     */
    var agcPtr: Long = 0L

    external fun srcInit(srcParams: SrcParams): Int
    external fun srcProcess(srcFilePath: String, dstFilePath: String): Int
    external fun nsInit(nsParams: NsParams): Int
    external fun nsProcess(srcFilePath: String, dstFilePath: String): Int
    external fun nsFree(): Int
    external fun agcInit(agcParams: AgcParams): Int
    external fun agcProcess(srcFilePath: String, dstFilePath: String): Int
    external fun agcFree(): Int

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("audio-lib")
        }
    }

}