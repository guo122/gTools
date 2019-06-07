//
//  MtkController.m
//  gBrick
//
//  Created by guo122 on 2019/4/29.
//  Copyright © 2019 John. All rights reserved.
//

@import MetalKit;

#import "gShaderTypes.h"
#import "MtkController.h"

@interface MtkController ()

@property (nonatomic, assign) vector_uint2 viewportSize;
@property (nonatomic, strong) id<MTLRenderPipelineState> pipelineState;
@property (nonatomic, strong) id<MTLCommandQueue> commandQueue;
@property (nonatomic, strong) id<MTLTexture> texture;
@property (nonatomic, strong) NSMutableArray<id<MTLBuffer>> * vertices;
@property (nonatomic, strong) NSMutableArray * numVertices;

@end

@implementation MtkController

-(void) Init: (UIViewController*)ViewController
{
    self.device = MTLCreateSystemDefaultDevice();
    self.delegate = self;
    self.viewportSize = (vector_uint2){self.drawableSize.width, self.drawableSize.height};
    
    self.vertices = [[NSMutableArray alloc]init];
    self.numVertices = [[NSMutableArray alloc]init];
    [self setupPipeline];
}

-(void) DrawRect: (CGRect)bounds :(vector_uint4)color
{
//    GVertex gVertices[] =
//    {
//        {{bounds.origin.x, bounds.origin.y, 0.0, 1.0}, {color[0], color[1], color[2]}},
//        {{bounds.origin.x, bounds.origin.y + bounds.size.width, 0.0, 1.0}, {color[0], color[1], color[2]}},
//        {{bounds.origin.x + bounds.size.height, bounds.origin.y, 0.0, 1.0}, {color[0], color[1], color[2]}},
//    };
    GVertex gVertices[] =
    {
        {{-1.0, -1.0, 0.0, 1.0}, {color[0], color[1], color[2]}},
        {{-1.0, 0.0 , 0.0, 1.0}, {color[0], color[1], color[2]}},
        {{ 0.0, 0.0 , 0.0, 1.0}, {color[0], color[1], color[2]}},
    };
    
    id<MTLBuffer> vv = [self.device newBufferWithBytes:gVertices  length:sizeof(gVertices) options:MTLResourceStorageModeShared];
    [self.vertices addObject:vv];
    
    NSUInteger num = sizeof(gVertices) / sizeof(GVertex);
    NSValue *tmpValue = [NSValue value: &num withObjCType:@encode(NSUInteger)];
    
    [self.numVertices addObject:tmpValue];
}

-(vector_uint2) GetDrawableSize
{
    return self.viewportSize;
}

// 设置渲染管道
-(void)setupPipeline {
    id<MTLLibrary> defaultLibrary = [self.device newDefaultLibrary]; // .metal
    id<MTLFunction> vertexFunction = [defaultLibrary newFunctionWithName:@"vertexShader"]; // 顶点shader，vertexShader是函数名
    id<MTLFunction> fragmentFunction = [defaultLibrary newFunctionWithName:@"samplingShader"]; // 片元shader，samplingShader是函数名
    
    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineStateDescriptor.vertexFunction = vertexFunction;
    pipelineStateDescriptor.fragmentFunction = fragmentFunction;
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = self.colorPixelFormat;
    self.pipelineState = [self.device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor
                                                                               error:NULL]; // 创建图形渲染管道，耗性能操作不宜频繁调用
    self.commandQueue = [self.device newCommandQueue]; // CommandQueue是渲染指令队列，保证渲染指令有序地提交到GPU
}

#pragma mark - delegate

- (void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size
{
    self.viewportSize = (vector_uint2){size.width, size.height};
}

- (void)drawInMTKView:(MTKView *)view
{
    id<MTLCommandBuffer> commandBuffer = [self.commandQueue commandBuffer];
    MTLRenderPassDescriptor *renderPassDescriptor = view.currentRenderPassDescriptor;
    
    if(renderPassDescriptor != nil)
    {
        renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(0.5, 1.0, 1.0, 1.0f); // 设置默认颜色
        id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor]; //编码绘制指令的Encoder
        [renderEncoder setViewport:(MTLViewport){0.0, 0.0, self.viewportSize.x, self.viewportSize.y, -1.0, 1.0 }]; // 设置显示区域
        
        NSUInteger i = 0;
        NSUInteger tmpNum;
        for (id<MTLBuffer> cur in self.vertices)
        {
            [[self.numVertices objectAtIndex:i]getValue:&tmpNum];
            
            [renderEncoder setRenderPipelineState:self.pipelineState]; // 设置渲染管道，以保证顶点和片元两个shader会被调用
            
            [renderEncoder setVertexBuffer:cur
                                    offset:0
                                   atIndex:0]; // 设置顶点缓存
            
            [renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle
                              vertexStart:0
                              vertexCount:tmpNum]; // 绘制
            
        }
        [renderEncoder endEncoding]; // 结束
        
        [commandBuffer presentDrawable:view.currentDrawable]; // 显示
        
    }
    
    [commandBuffer commit];
}
@end
