import "lib/display" for Display
import "lib/input" for Input

class Application {
    static init() {
        Display.setTitle("Test Application")
        Display.setSize(1280, 720)
        Display.create()

        Input.add_action("cancel")
        Input.action_add_key("cancel", Input.get_key_code("Escape"))
        Input.add_action("up")
        Input.action_add_key("up", Input.get_key_code("W"))
        Input.add_action("down")
        Input.action_add_key("down", Input.get_key_code("S"))
    }

    static run() {
        init()

        while (!Display.isCloseRequested()) {
            Display.update()

            if (Input.is_action_just_pressed("cancel")) {
                Display.close()
            }

            if (Input.is_action_just_pressed("up")) {
                System.print("Up is being pressed")
            } else {
                if (Input.is_action_just_pressed("down")) {
                    System.print("Down is being pressed")
                }
            }
        }

        Display.destroy()
    }
}

Application.run()