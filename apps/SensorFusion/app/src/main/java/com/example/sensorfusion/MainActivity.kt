package com.example.sensorfusion

import android.content.res.AssetManager
import android.opengl.GLSurfaceView
import android.opengl.GLSurfaceView.Renderer
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    lateinit var mView: GLSurfaceView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        mView = GLSurfaceView(application)
        mView.setEGLContextClientVersion(2)
        mView.setRenderer(object: Renderer {
            override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
                surfaceCreated()
            }
            override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
                surfaceChanged(width, height)
            }
            override fun onDrawFrame(gl: GL10) {
                drawFrame()
            }
        })
        mView.queueEvent({init(assets)})
        setContentView(mView)
    }

    override fun onPause() {
        super.onPause()
        mView.onPause()
        mView.queueEvent(this::pause)
    }

    override fun onResume() {
        super.onResume()
        mView.onResume()
        mView.queueEvent(this::resume)
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String
    external fun init(assMan: AssetManager)
    external fun surfaceCreated()
    external fun surfaceChanged(width: Int, height: Int)
    external fun drawFrame()
    external fun pause()
    external fun resume()

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}
