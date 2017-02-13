//
//  Renderer.swift
//  4KTest
//
//  Created by cafe on 13/02/2017.
//  Copyright © 2017 Hellicar Studio. All rights reserved.
//

import Metal
import MetalKit

struct Vertex {
    var position: float4
    var color: float4
}

class Renderer : NSObject, MTKViewDelegate {
    
    weak var view: MTKView!
    
    let device = MTLCreateSystemDefaultDevice()
    var commandQueue: MTLCommandQueue! = nil
    var renderPipelineState: MTLRenderPipelineState! = nil
    var depthStencilState: MTLDepthStencilState! = nil
    var sampler: MTLSamplerState! = nil
    var texture: MTLTexture! = nil
    
    
    var vertices: [Vertex]! //  create an array of floats of the CPU
    
    let vertexBuffer: MTLBuffer!

    
    
    init?(mtkView: MTKView) {
        super.init()
        
        let vert = Vertex(
        
        vertexBuffer = device?.makeBuffer(bytes: &vertices, length: <#T##Int#>, options: <#T##MTLResourceOptions#>)
//        view = mtkView
//        
//        view.clearColor = MTLClearColorMake(1, 1, 1, 1)
//        view.colorPixelFormat = .bgra8Unorm
//        view.depthStencilPixelFormat = .depth32Float
//        
//        if let defaultDevice = MTLCreateSystemDefaultDevice() {
//            device = defaultDevice
//        } else {
//            print("Metal is not supported")
//            return nil
//        }
//        
//        commandQueue = device.makeCommandQueue()
//        
//        do {
//           renderPipelineState = try Renderer.buildRenderPipelineWithDevice(device, view: mtkView)
//        }
//        catch {
//            print("Unable to compile render pipeline state")
//            return nil
//        }
        
    }
    
    class func buildRenderPipelineWithDevice(_ device: MTLDevice, view: MTKView) throws -> MTLRenderPipelineState {
        // The default library contains all of the shader functions that were compiled into our app bundle
        let library = device.newDefaultLibrary()!
        
        // Retrieve the functions that will comprise our pipeline
        let vertexFunction = library.makeFunction(name: "vertex_transform")
        let fragmentFunction = library.makeFunction(name: "fragment_lit_textured")
        
        // A render pipeline descriptor describes the configuration of our programmable pipeline
        let pipelineDescriptor = MTLRenderPipelineDescriptor()
        pipelineDescriptor.label = "Render Pipeline"
        pipelineDescriptor.sampleCount = view.sampleCount
        pipelineDescriptor.vertexFunction = vertexFunction
        pipelineDescriptor.fragmentFunction = fragmentFunction
        pipelineDescriptor.colorAttachments[0].pixelFormat = view.colorPixelFormat
        pipelineDescriptor.depthAttachmentPixelFormat = view.depthStencilPixelFormat
        
        return try device.makeRenderPipelineState(descriptor: pipelineDescriptor)
    }

    
    func render(_ view: MTKView) {
//        let commandBuffer = commandQueue.makeCommandBuffer()
//        
//        // Ask the view for a render pass descriptor. It will have a loadAction of MTLLoadActionClear and have the clear color of the drawable set to our desired clear color.
//        let renderPassDescriptor = view.currentRenderPassDescriptor
//        
//        if let renderPassDescriptor = renderPassDescriptor {
//            //create a render encoder to clear the screen adn raw out objects
//            let renderEncoder = commandBuffer.makeRenderCommandEncoder(descriptor: renderPassDescriptor)
//            
//            renderEncoder.pushDebugGroup("DrawTriangle")
//            
//            renderEncoder.setFrontFacing(.counterClockwise)
//            
//            renderEncoder.setRenderPipelineState(renderPipelineState)
//            
//           // renderEncoder.setVertexBuffer(vertexBuffer, offset:0, at: 0)
//            
//            renderEncoder.drawIndexedPrimitives(.triangle,
//                                                indexCount: 3,
//                                                indexType: .uInt16,
//                                                indexBuffer: indexBuffer,
//                                                indexBufferOffset: 0)
//            
//            renderEncoder.popDebugGroup()
//            
//            renderEncodert.endEncoding()
//        }
    }
    
    func mtkView(_ view: MTKView, drawableSizeWillChange size: CGSize) {
        // respond to resize
    }
    
    @objc(drawInMTKView:)
    func draw(in metalView: MTKView)
    {
        render(metalView)
    }

}
