class Application {
    static run() {
        var start = System.clock
        for (i in 1...999999) {
            System.print("Count: %(i)")
        }
        var end = System.clock
        System.print("Duration: %(end - start)")
    }
}