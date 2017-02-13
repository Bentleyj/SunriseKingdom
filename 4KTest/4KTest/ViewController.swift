//
//  ViewController.swift
//  4KTest
//
//  Created by James Bentley on 2/11/17.
//  Copyright © 2017 Hellicar Studio. All rights reserved.
//

import Cocoa
import AVKit
import AVFoundation

class ViewController: NSViewController {

    @IBOutlet weak var playWindow: AVPlayerView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        var player: AVPlayer
        guard let path = Bundle.main.url(forResource: "video4K", withExtension: "mp4") else {
            debugPrint("video not loaded")
            return
        }
        player = AVPlayer(url: path)
        playWindow.player = player
        player.play()
        
        // Do any additional setup after loading the view.
    }

    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }


}

