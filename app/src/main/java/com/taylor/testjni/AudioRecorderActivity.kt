package com.taylor.testjni

import android.Manifest
import android.annotation.SuppressLint
import android.content.pm.PackageManager
import android.os.Build
import android.os.Bundle
import android.view.MotionEvent
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import kotlinx.coroutines.MainScope
import kotlinx.coroutines.launch
import util.AudioManager
import java.io.File
import util.*
import util.AudioManager.Companion.SAMPLE_RATE

@SuppressLint("ClickableViewAccessibility")
class AudioRecorderActivity : AppCompatActivity() {

    private var pcmFile: File? = null
    private var mediaFile: File? = null
    private var goodPcmFile: File? = null
    private val audioManager by lazy {
        AudioManager(this, AudioManager.PCM).apply {
            onRecordSuccess = { file: File, l: Long ->
                pcmFile = file
            }
        }
    }

    private val _44100AudioTrackManager = AudioTrackManager(44100)
    private val _32000AudioTrackManager = AudioTrackManager(32000)
    private val audioJniUtil = AudioJniUtil()
    private val mainScope = MainScope()

    private val mediaManager by lazy {
        AudioManager(this, AudioManager.AAC).apply {
            onRecordSuccess = { file: File, l: Long ->
                mediaFile = file
            }
        }
    }

    private val contentView by lazy {
        ConstraintLayout {
            layout_width = match_parent
            layout_height = match_parent

            Button {
                layout_id = "btnAudioRecorder"
                layout_width = wrap_content
                layout_height = wrap_content
                text = "start"
                textAllCaps = false
                textSize = 30f
                start_toStartOf = parent_id
                end_toStartOf = "btnMediaRecorder"
                center_vertical = true
                padding = 10
                shape = shape {
                    corner_radius = 40
                    solid_color = "#ff00ff"
                }
                setOnTouchListener { v, event ->
                    when (event.action) {
                        MotionEvent.ACTION_DOWN -> {
                            startAudioRecord()
                        }
                        MotionEvent.ACTION_UP -> {
                            stopAudioRecord()
                        }
                    }

                    false
                }
            }

            TextView {
                layout_id = "tvAudioRecorder"
                layout_width = wrap_content
                layout_height = wrap_content
                textSize = 12f
                text = "AudioRecorder"
                gravity = gravity_center
                align_horizontal_to = "btnAudioRecorder"
                top_toBottomOf = "btnAudioRecorder"
            }

            Button {
                layout_id = "btnMediaRecorder"
                layout_width = wrap_content
                layout_height = wrap_content
                text = "start"
                textAllCaps = false
                start_toEndOf = "btnAudioRecorder"
                end_toEndOf = parent_id
                padding = 10
                center_vertical = true
                textSize = 30f
                shape = shape {
                    corner_radius = 40
                    solid_color = "#ff00ff"
                }
                setOnTouchListener { v, event ->
                    when (event.action) {
                        MotionEvent.ACTION_DOWN -> {
                            startMediaRecord()
                        }
                        MotionEvent.ACTION_UP -> {
                            stopMediaRecord()
                        }
                    }

                    false
                }

            }

            TextView {
                layout_id = "tvMediaRecorder"
                layout_width = wrap_content
                layout_height = wrap_content
                textSize = 12f
                text = "MediaRecorder"
                gravity = gravity_center
                align_horizontal_to = "btnMediaRecorder"
                top_toBottomOf = "btnMediaRecorder"
            }

            TextView {
                layout_id = "tvPlayAudioRecord"
                layout_width = wrap_content
                layout_height = wrap_content
                textSize = 20f
                textColor = "#ffffff"
                text = "play"
                gravity = gravity_center
                padding = 10
                align_horizontal_to = "tvAudioRecorder"
                top_toBottomOf = "tvAudioRecorder"
                shape = shape {
                    corner_radius = 20
                    solid_color = "#0000ff"
                }
                onClick = {
                    playPcm(pcmFile, SAMPLE_RATE)
                }
            }

            TextView {
                layout_id = "tvPlayMediaRecord"
                layout_width = wrap_content
                layout_height = wrap_content
                textSize = 20f
                textColor = "#ffffff"
                text = "play"
                gravity = gravity_center
                padding = 10
                align_horizontal_to = "tvMediaRecorder"
                top_toBottomOf = "tvMediaRecorder"
                shape = shape {
                    corner_radius = 20
                    solid_color = "#0000ff"
                }
                onClick = {
                    mediaFile?.absolutePath?.let {

                    }
                }
            }

            TextView {
                layout_id = "src"
                layout_width = wrap_content
                layout_height = wrap_content
                textSize = 20f
                textColor = "#ffffff"
                text = "src+ns"
                gravity = gravity_center
                start_toStartOf = parent_id
                top_toTopOf = parent_id
                padding = 10
                shape = shape {
                    solid_color = "#ff00ff"
                    corner_radius = 10
                }
                onClick = {
                    src_ns()
                }
            }

            TextView {
                layout_id = "playGoodPcm"
                layout_width = wrap_content
                layout_height = wrap_content
                textSize = 20f
                textColor = "#ffffff"
                text = "play good pcm"
                gravity = gravity_center
                start_toEndOf = "src"
                margin_start = 10
                top_toTopOf = parent_id
                padding = 10
                shape = shape {
                    solid_color = "#ff00ff"
                    corner_radius = 10
                }
                onClick = {
                    playPcm(goodPcmFile, 44100)
                }
            }

            TextView {
                layout_id = "monitor"
                layout_width = wrap_content
                layout_height = wrap_content
                textSize = 30f
                textColor = "#ffffff"
                text = "pcm to aac"
                gravity = gravity_center
                top_toBottomOf = "src"
                start_toStartOf = parent_id
                margin_top = 10
                shape = shape {
                    solid_color = "#ff00ff"
                    corner_radius = 10
                }
                onClick = {
                    pcmFile?.let {
                        val aacFile = File(it.absolutePath.dropLast(4) + ".aac")
//                        AacPcmCoder.encodePcmToAac(audioFile,aacFile)
                        mainScope.launch { PcmEncoder.toAac(pcmFile, aacFile) }
                    }
                }
            }
        }
    }

    private fun playPcm(pcmFile: File?, sampleRate: Int) {
        pcmFile?.absolutePath?.let {
            if (sampleRate == 44100) _44100AudioTrackManager.startPlay(it)
            else if (sampleRate == 32000) _32000AudioTrackManager.startPlay(it)
        }
    }

    private fun src_ns() {
//        audioJniUtil.srcInit(SrcParams().apply {
//            inSampleRate = SAMPLE_RATE
//            outSampleRate = OUT_SAMPLE_RATE
//            channel = 1
//            quality = 4
//        })
        audioJniUtil.nsInit(NsParams().apply {
            fs = 32000
            maxDenoiseDb = -20
        })
        pcmFile?.let {
//            val srcOutFile = File(it.absolutePath.dropLast(4) + "-src.pcm")
//            audioJniUtil.srcProcess(it.absolutePath, srcOutFile.absolutePath)
            val nsOutFile = File(it.absolutePath.dropLast(4) + "-ns.pcm")
            audioJniUtil.nsProcess(it.absolutePath, nsOutFile.absolutePath)
            goodPcmFile = nsOutFile
            pcmToAac(nsOutFile)
        }
    }

    private fun pcmToAac(pcmFile: File?) {
        pcmFile?.let {
            val aacFile = File(it.absolutePath.dropLast(4) + ".aac")
            mainScope.launch { PcmEncoder.toAac(pcmFile, aacFile) }
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(contentView)
        if (Build.VERSION.SDK_INT >= 23) {
            if (ContextCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED || ContextCompat.checkSelfPermission(
                    this,
                    Manifest.permission.WRITE_EXTERNAL_STORAGE
                ) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(this, listOf(Manifest.permission.RECORD_AUDIO, Manifest.permission.WRITE_EXTERNAL_STORAGE).toTypedArray(), 1)
            }
        }
    }

    private fun startAudioRecord() {
        audioManager.start()
    }

    private fun startMediaRecord() {
        mediaManager.start()
    }

    private fun stopAudioRecord() {
        audioManager.stop()
    }

    private fun stopMediaRecord() {
        mediaManager.stop()
    }
}

