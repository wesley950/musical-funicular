import "lib/display" for Display

class Application {
    static init() {
        Display.setTitle("Test Application")
        Display.setSize(1280, 720)
        Display.create()
    }

    static run() {
        init()

        while (!Display.isCloseRequested()) {
            Display.update()
        }

        Display.destroy()
    }
}

Application.run()