//
//  Shaders.metal
//  4KTest
//
//  Created by cafe on 13/02/2017.
//  Copyright © 2017 Hellicar Studio. All rights reserved.
//

#include <metal_stdlib>
using namespace metal;

struct VertexIn {
    float4 position [[position]];
    float2 texCoords;
};

struct VertexOut {
    float4 position [[position]];
    float2 texCoords;
};

vertex VertexOut vertex_func(constant VertexIn *vertices [[buffer(0)]],
                          uint vid [[vertex_id]])
{
    VertexOut out;
    out.position = vertices[vid].position;
    out.texCoords = vertices[vid].texCoords;
    return out;
}

fragment half4 fragment_func(VertexOut fragmentIn [[stage_in]],
                             texture2d<float, access::sample> tex2d [[texture(0)]],
                             sampler sampler2d [[sampler(0)]])
{
    // Sample the Texture
    half3 textureColor = half3(tex2d.sample(sampler2d, fragmentIn.texCoords).rgb);
    return half4(textureColor, 1.0);
}


