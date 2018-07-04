//
//  ViewController.swift
//  SwiftTest
//
//  Created by cafe on 14/02/2017.
//  Copyright © 2017 Hellicar Studio. All rights reserved.
//

import Cocoa
import AVKit
import AVFoundation

class ViewController: NSViewController {
    
    @IBOutlet weak var playerView: AVPlayerView!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        
        guard let path = Bundle.main.url(forResource: "video4K", withExtension: "mp4") else {
            debugPrint("video not loaded")
            return
        }
        
        let player = AVPlayer(url: path)
        
        playerView.player = player
        
        player.play()
        
    }

    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }


}

