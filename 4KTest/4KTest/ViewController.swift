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
        
    @IBOutlet weak var playerView: AVPlayerView!
    @IBOutlet var metalView: MetalView!
    var player: AVPlayer!

    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        metalView.onViewDidLoad()
    }

    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }
}

