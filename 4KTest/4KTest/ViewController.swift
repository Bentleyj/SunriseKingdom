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
import Metal
import MetalKit

class ViewController: NSViewController, MTKViewDelegate {

    @IBOutlet weak var playWindow: AVPlayerView!
        
    var device: MTLDevice! = nil
    var metalLayer: CAMetalLayer! = nil
    
    
    var vertexBuffer: MTLBuffer! = nil
    
    var pipelineState: MTLRenderPipelineState! = nil
    
    var commandQueue: MTLCommandQueue! = nil
    
    //var view: MTKView! = nil
    
    override func viewDidLoad() {
        super.viewDidLoad()
        var player: AVPlayer
        guard let path = Bundle.main.url(forResource: "video4K", withExtension: "mp4") else {
            debugPrint("video not loaded")
            return
        }
        player = AVPlayer(url: path)
        //playWindow.player = player
        player.play()
        
        device = MTLCreateSystemDefaultDevice() // Crate Device Handle
        metalLayer = CAMetalLayer() //Create Metal Layer
        metalLayer.device = device //Attach Metal Device to the Layer
        metalLayer.pixelFormat = .bgra8Unorm // Set Pixel Format: 8 bytes for Blue, red, Green and Alpha with values between 0 and 1
        metalLayer.framebufferOnly = true // Performance encacing line. This means I promise not to sample from the texture before I draw it
        metalLayer.frame = view.layer!.frame // Set the frame of the layer to match the frame of the view
        view.layer!.addSublayer(metalLayer) // add the layer we just made as a sub-layer of the views main layer
        
        let dataSize = vertexData.count * MemoryLayout.size(ofValue: vertexData[0]) // Get the size of the vertex buffer in bytes
        vertexBuffer = device.makeBuffer(bytes: vertexData, length: dataSize)
        
        let defaultLibrary = device.newDefaultLibrary();
        let fragmentProgram = defaultLibrary!.makeFunction(name: "basic_fragment")
        let vertexProgram = defaultLibrary!.makeFunction(name: "basic_vertex")
        
        let pipelineStateDescriptor = MTLRenderPipelineDescriptor()
        pipelineStateDescriptor.vertexFunction = vertexProgram;
        pipelineStateDescriptor.fragmentFunction = fragmentProgram;
        pipelineStateDescriptor.colorAttachments[0].pixelFormat = .bgra8Unorm
        
        //var pipelineError : NSError?
        do {
             try pipelineState = device.makeRenderPipelineState(descriptor: pipelineStateDescriptor)
        } catch {
            debugPrint("Failed to create pipeline state");
        }
        
    }
    
    func mtkView(_ view: MTKView, drawableSizeWillChange size: CGSize) {
        //respond to resize
    }
    
    func draw(in metalView: MTKView) {
        // Our command buffer is a container for the work we want to perform with the GPU.
        let commandBuffer = commandQueue.makeCommandBuffer()
        
        commandBuffer.commit();
        
        //
    }

    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }


}

