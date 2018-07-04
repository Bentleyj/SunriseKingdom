//
//  MetalView.swift
//  4KTest
//
//  Created by cafe on 14/02/2017.
//  Copyright © 2017 Hellicar Studio. All rights reserved.
//

import Cocoa
import MetalKit
import AVFoundation
import AVKit

class MetalView: MTKView {
    
    @IBOutlet weak var playerView: AVPlayerView!
    let vertex_data: [Float] = [-1.0, -1.0, 0.0, 1.0,
                                -1.0, 1.0, 0.0, 1.0,
                                1.0, -1.0, 0.0, 1.0,
                                -1.0, 1.0, 0.0, 1.0,
                                1.0, 1.0, 0.0, 1.0,
                                1.0, -1.0, 0.0, 1.0
                                ]
    
    
    var data_size: Int?
    var vertex_buffer: MTLBuffer?
    var library: MTLLibrary?
    var vertex_func: MTLFunction?
    var frag_func: MTLFunction?
    var rpld: MTLRenderPipelineDescriptor?
    
    var ciContext: CIContext?
    var image: CIImage?
    var texture: MTLTexture?
    var sampler: MTLSamplerState?
    
    var player: AVPlayer!
    
    var videoOutput = AVPlayerItemVideoOutput(pixelBufferAttributes: [
        String(kCVPixelBufferPixelFormatTypeKey): NSNumber(value: kCVPixelFormatType_420YpCbCr8BiPlanarFullRange)])
    
    required init(coder: NSCoder) {
        super.init(coder: coder)

        self.device = MTLCreateSystemDefaultDevice()!
        data_size = vertex_data.count * MemoryLayout<Float>.stride
        vertex_buffer = device!.makeBuffer(bytes: vertex_data, length: data_size!, options: [])
        library = self.device!.newDefaultLibrary()!
        vertex_func = library!.makeFunction(name: "vertex_func")!
        frag_func = library!.makeFunction(name: "fragment_func")!
        sampler = buildSamplerStateWithDevice(device!, addressMode: .repeat, filter: .linear)

        rpld = MTLRenderPipelineDescriptor()
        rpld!.vertexFunction = vertex_func
        rpld!.fragmentFunction = frag_func
        rpld!.colorAttachments[0].pixelFormat = .bgra8Unorm
        
        let textureDescriptor = MTLTextureDescriptor.texture2DDescriptor(pixelFormat: .bgra8Unorm, width: 256, height: 256, mipmapped: false)
        texture = device?.makeTexture(descriptor: textureDescriptor)
    }
    
    func onViewDidLoad() {
        //Setup and play our video player
        guard let path = Bundle.main.url(forResource: "video4K", withExtension: "mp4") else {
            debugPrint("video not loaded")
            return
        }
        player = AVPlayer(url: path)
        
        playerView.player = player
        
        let currentItem = player.currentItem
        currentItem!.add(videoOutput)
        
        player.play()
        
        ciContext = CIContext(mtlDevice: self.device!)

    }
    
    func render() {
        if videoOutput.hasNewPixelBuffer(forItemTime: player.currentTime()) {
            var presentationItemTime = kCMTimeZero
            let pixelBuffer = videoOutput.copyPixelBuffer(forItemTime: player.currentTime(), itemTimeForDisplay: &presentationItemTime)
            image = CIImage(cvImageBuffer: pixelBuffer!)
            renderMetalTexture()
        }
        let rps = try! device!.makeRenderPipelineState(descriptor: rpld!)
        if let rpd = currentRenderPassDescriptor, let drawable = currentDrawable {
            rpd.colorAttachments[0].clearColor = MTLClearColorMake(0, 0.5, 0.5, 1.0)
            let command_buffer = self.device!.makeCommandQueue().makeCommandBuffer()
            let command_encoder = command_buffer.makeRenderCommandEncoder(descriptor: rpd)
            command_encoder.setRenderPipelineState(rps)
            command_encoder.setVertexBuffer(vertex_buffer, offset: 0, at: 0)
            command_encoder.setFragmentTexture(texture, at: 0)
            command_encoder.setFragmentSamplerState(sampler, at: 0)
            command_encoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 6, instanceCount: 1)
            command_encoder.endEncoding()
            command_buffer.present(drawable)
            command_buffer.commit()
        }
    }
    
    func renderMetalTexture() {
        guard let img = image, let tex = texture else {
            return
        }
        let rect = CGRect(x: 0, y: 0, width: 256, height: 256)
        let colorSpace = img.colorSpace ?? CGColorSpaceCreateDeviceRGB()
        ciContext!.render(img, to: tex, commandBuffer: nil, bounds: rect, colorSpace: colorSpace)
    }
    
    func buildSamplerStateWithDevice(_ device: MTLDevice,
                                           addressMode: MTLSamplerAddressMode,
                                           filter: MTLSamplerMinMagFilter) -> MTLSamplerState
    {
        let samplerDescriptor = MTLSamplerDescriptor()
        samplerDescriptor.sAddressMode = addressMode
        samplerDescriptor.tAddressMode = addressMode
        samplerDescriptor.minFilter = filter
        samplerDescriptor.magFilter = filter
        return device.makeSamplerState(descriptor: samplerDescriptor)
    }
    
    override func draw(_ dirtyRect: NSRect) {
        super.draw(dirtyRect)
        render()
    }
}
