//
//  MtkController.m
//  gBrick
//
//  Created by guo122 on 2019/4/29.
//  Copyright © 2019 John. All rights reserved.
//

@import MetalKit;
@import GLKit;

#import "gShaderTypes.h"
#import "MtkController.h"

@interface MtkController ()

@property (nonatomic, strong) UIViewController *vc;

@property (nonatomic, assign) vector_uint2 viewportSize;
@property (nonatomic, strong) id<MTLRenderPipelineState> pipelineState;
@property (nonatomic, strong) id<MTLCommandQueue> commandQueue;
//@property (nonatomic, strong) id<MTLTexture> texture;
//@property (nonatomic, strong) NSMutableArray<id<MTLBuffer>> * vertices;
//@property (nonatomic, strong) NSMutableArray<id<MTLBuffer>> * indices;
//@property (nonatomic, strong) NSMutableArray * numVertices;

@property (nonatomic, strong) id<MTLBuffer> vertices;
@property (nonatomic, strong) id<MTLBuffer> indexs;
@property (nonatomic, assign) NSUInteger indexCount;

@end

@implementation MtkController

-(void) Init: (UIViewController*)ViewController
{
    NSLog(@"[init] MtkController init.");
    
    self.framebufferOnly = true;
    self.vc = ViewController;
    self.device = MTLCreateSystemDefaultDevice();
    self.delegate = self;
    self.viewportSize = (vector_uint2){self.drawableSize.width, self.drawableSize.height};
    
//    self.indices = [[NSMutableArray alloc]init];
//    self.vertices = [[NSMutableArray alloc]init];
//    self.numVertices = [[NSMutableArray alloc]init];
    [self setupPipeline];
    [self setupVertex];
}

-(void) DrawRect: (CGRect)bounds :(vector_uint4)color
{
//    CGFloat localX = ( 2 * bounds.origin.x ) - 1;
//    CGFloat localY = 1 - ( 2 * bounds.origin.y );
//    CGFloat localHeight = bounds.size.height * 2;
//    CGFloat localWidth = bounds.size.width * 2;
//
//    GVertex gVertices[] =
//    {
//        {{ localX               , localY                , 0.0, 1.0}, {color[0], color[1], color[2]}},
//        {{ localX + localWidth  , localY                , 0.0, 1.0}, {color[0], color[1], color[2]}},
//        {{ localX + localWidth  , localY - localHeight  , 0.0, 1.0}, {color[0], color[1], color[2]}},
//        {{ localX               , localY - localHeight  , 0.0, 1.0}, {color[0], color[1], color[2]}},
//    };
//
//    int gindices[] =
//    {
//        0, 1, 3,
//        1, 2, 3,
//    };
//
//    id<MTLBuffer> ii = [self.device newBufferWithBytes:gindices length:sizeof(gindices) options:MTLResourceStorageModeShared];
//    [self.indices addObject:ii];
//
//    id<MTLBuffer> vv = [self.device newBufferWithBytes:gVertices  length:sizeof(gVertices) options:MTLResourceStorageModeShared];
//    [self.vertices addObject:vv];
//
//    NSUInteger num = sizeof(gindices) / sizeof(int);
//    NSValue *tmpValue = [NSValue value: &num withObjCType:@encode(NSUInteger)];
//    [self.numVertices addObject:tmpValue];
//
//
//
//
//
//    static const GVertex quadVertices[] =
//    {  // 顶点坐标                          顶点颜色                    纹理坐标
//        {{-0.5f, 0.5f, 0.0f, 1.0f},      {0.0f, 0.0f, 0.5f}},
//        {{0.5f, 0.5f, 0.0f, 1.0f},       {0.0f, 0.5f, 0.0f}},
//        {{-0.5f, -0.5f, 0.0f, 1.0f},     {0.5f, 0.0f, 1.0f}},
//        {{0.5f, -0.5f, 0.0f, 1.0f},      {0.0f, 0.0f, 0.5f}},
//        {{0.0f, 0.0f, 1.0f, 1.0f},       {1.0f, 1.0f, 1.0f}},
//    };
//    self.svertices = [self.device newBufferWithBytes:quadVertices
//                                                     length:sizeof(quadVertices)
//                                                    options:MTLResourceStorageModeShared];
//    static int indices[] =
//    { // 索引
//        0, 3, 2,
//        0, 1, 3,
//        //        0, 2, 4,
//        //        0, 4, 1,
//        //        2, 3, 4,
//        //        1, 4, 3,
//    };
//    self.sindexs = [self.device newBufferWithBytes:indices
//                                                   length:sizeof(indices)
//                                                  options:MTLResourceStorageModeShared];
//    self.sindexCount = sizeof(indices) / sizeof(int);
}

-(vector_uint2) GetDrawableSize
{
    return self.viewportSize;
}

//// 设置渲染管道
//-(void)setupPipeline {
//    id<MTLLibrary> defaultLibrary = [self.device newDefaultLibrary]; // .metal
//    id<MTLFunction> vertexFunction = [defaultLibrary newFunctionWithName:@"vertexShader"]; // 顶点shader，vertexShader是函数名
//    id<MTLFunction> fragmentFunction = [defaultLibrary newFunctionWithName:@"samplingShader"]; // 片元shader，samplingShader是函数名
//
//    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
//    pipelineStateDescriptor.vertexFunction = vertexFunction;
//    pipelineStateDescriptor.fragmentFunction = fragmentFunction;
//    pipelineStateDescriptor.colorAttachments[0].pixelFormat = self.colorPixelFormat;
//    self.pipelineState = [self.device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor
//                                                                               error:NULL]; // 创建图形渲染管道，耗性能操作不宜频繁调用
//    self.commandQueue = [self.device newCommandQueue]; // CommandQueue是渲染指令队列，保证渲染指令有序地提交到GPU
//}
//
//- (matrix_float4x4)getMetalMatrixFromGLKMatrix:(GLKMatrix4)matrix {
//    matrix_float4x4 ret = (matrix_float4x4){
//        simd_make_float4(matrix.m00, matrix.m01, matrix.m02, matrix.m03),
//        simd_make_float4(matrix.m10, matrix.m11, matrix.m12, matrix.m13),
//        simd_make_float4(matrix.m20, matrix.m21, matrix.m22, matrix.m23),
//        simd_make_float4(matrix.m30, matrix.m31, matrix.m32, matrix.m33),
//    };
//    return ret;
//}
//
//- (void)setupMatrixWithEncoder:(id<MTLRenderCommandEncoder>)renderEncoder {
//    CGSize size = self.vc.view.bounds.size;
//    float aspect = fabs(size.width / size.height);
//    GLKMatrix4 projectionMatrix = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(90.0), aspect, 0.1f, 10.f);
//    GLKMatrix4 modelViewMatrix = GLKMatrix4Translate(GLKMatrix4Identity, 0.0f, 0.0f, -2.0f);
//    static float x = 12.0, y = 0.0, z = M_PI;
//
//    x += 0.1;
//
//    modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, x, 1, 0, 0);
//    modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, y, 0, 1, 0);
//    modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, z, 0, 0, 1);
//
//    GMatrix matrix = {[self getMetalMatrixFromGLKMatrix:projectionMatrix], [self getMetalMatrixFromGLKMatrix:modelViewMatrix]};
//
//    [renderEncoder setVertexBytes:&matrix
//                           length:sizeof(matrix)
//                          atIndex:1];
//}
//
//#pragma mark - delegate
//
//- (void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size
//{
//    self.viewportSize = (vector_uint2){size.width, size.height};
//}
//
//- (void)drawInMTKView:(MTKView *)view
//{
////    id<MTLCommandBuffer> commandBuffer = [self.commandQueue commandBuffer];
////    MTLRenderPassDescriptor *renderPassDescriptor = view.currentRenderPassDescriptor;
////
////    if(renderPassDescriptor != nil)
////    {
////        renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(0.5, 1.0, 1.0, 1.0f); // 设置默认颜色
////        renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
////
////        id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor]; //编码绘制指令的Encoder
////
////        [renderEncoder setViewport:(MTLViewport){0.0, 0.0, self.viewportSize.x, self.viewportSize.y, -1.0, 1.0 }]; // 设置显示区域
////
////        NSUInteger i = 0;
////        NSUInteger tmpNum;
////        for (id<MTLBuffer> cur in self.vertices)
////        {
////            [[self.numVertices objectAtIndex:i]getValue:&tmpNum];
////
////            [renderEncoder setRenderPipelineState:self.pipelineState]; // 设置渲染管道，以保证顶点和片元两个shader会被调用
////
////            [self setupMatrixWithEncoder:renderEncoder];
////
////            [renderEncoder setVertexBuffer:cur
////                                    offset:0
////                                   atIndex:GVertexInputIndexVertices]; // 设置顶点缓存
////            [renderEncoder setFrontFacingWinding:MTLWindingCounterClockwise];
//////            [renderEncoder setCullMode:MTLCullModeBack];
////
////            [renderEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle
////                                      indexCount:tmpNum
////                                       indexType:MTLIndexTypeUInt32
////                                     indexBuffer:[self.indices objectAtIndex:i]
////                               indexBufferOffset:0];
////        }
////        [renderEncoder endEncoding]; // 结束
////
////        [commandBuffer presentDrawable:view.currentDrawable]; // 显示
////
////    }
////
////    [commandBuffer commit];
//
//
//
//    id<MTLCommandBuffer> commandBuffer = [self.commandQueue commandBuffer];
//    MTLRenderPassDescriptor *renderPassDescriptor = view.currentRenderPassDescriptor;
//
//    if(renderPassDescriptor != nil)
//    {
//        renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(0.0, 0.5, 0.5, 1.0f);
//        renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
//
//        id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
//
//        [renderEncoder setViewport:(MTLViewport){0.0, 0.0, self.viewportSize.x, self.viewportSize.y, -1.0, 1.0 }];
//        [renderEncoder setRenderPipelineState:self.pipelineState];
//        [self setupMatrixWithEncoder:renderEncoder];
//
//        [renderEncoder setVertexBuffer:self.svertices
//                                offset:0
//                               atIndex:0];
//        [renderEncoder setFrontFacingWinding:MTLWindingCounterClockwise];
//        [renderEncoder setCullMode:MTLCullModeBack];
//
//        [renderEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle
//                                  indexCount:self.sindexCount
//                                   indexType:MTLIndexTypeUInt32
//                                 indexBuffer:self.sindexs
//                           indexBufferOffset:0];
//
//        [renderEncoder endEncoding];
//
//        [commandBuffer presentDrawable:view.currentDrawable];
//    }
//
//    [commandBuffer commit];
//}

-(void)setupPipeline {
    id<MTLLibrary> defaultLibrary = [self.device newDefaultLibrary];
    id<MTLFunction> vertexFunction = [defaultLibrary newFunctionWithName:@"vertexShader"];
    id<MTLFunction> fragmentFunction = [defaultLibrary newFunctionWithName:@"samplingShader"];
    
    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineStateDescriptor.vertexFunction = vertexFunction;
    pipelineStateDescriptor.fragmentFunction = fragmentFunction;
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = self.colorPixelFormat;
    self.pipelineState = [self.device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor
                                                                             error:NULL];
    self.commandQueue = [self.device newCommandQueue];
}

- (void)setupVertex {
    static const GVertex quadVertices[] =
    {  // 顶点坐标                          顶点颜色                    纹理坐标
        {{-0.5f, 0.5f, 0.0f, 1.0f},      {0.0f, 0.0f, 0.5f}},
        {{0.5f, 0.5f, 0.0f, 1.0f},       {0.0f, 0.5f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f, 1.0f},     {0.5f, 0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.0f, 1.0f},      {0.0f, 0.0f, 0.5f}},
        {{0.0f, 0.0f, 1.0f, 1.0f},       {1.0f, 1.0f, 1.0f}},
    };
    self.vertices = [self.device newBufferWithBytes:quadVertices
                                                     length:sizeof(quadVertices)
                                                    options:MTLResourceStorageModeShared];
    static int indices[] =
    { // 索引
        0, 3, 2,
        0, 1, 3,
        //        0, 2, 4,
        //        0, 4, 1,
        //        2, 3, 4,
        //        1, 4, 3,
    };
    self.indexs = [self.device newBufferWithBytes:indices
                                                   length:sizeof(indices)
                                                  options:MTLResourceStorageModeShared];
    self.indexCount = sizeof(indices) / sizeof(int);
}

/**
 找了很多文档，都没有发现metalKit或者simd相关的接口可以快捷创建矩阵的，于是只能从GLKit里面借力
 
 @param matrix GLKit的矩阵
 @return metal用的矩阵
 */
- (matrix_float4x4)getMetalMatrixFromGLKMatrix:(GLKMatrix4)matrix {
    matrix_float4x4 ret = (matrix_float4x4){
        simd_make_float4(matrix.m00, matrix.m01, matrix.m02, matrix.m03),
        simd_make_float4(matrix.m10, matrix.m11, matrix.m12, matrix.m13),
        simd_make_float4(matrix.m20, matrix.m21, matrix.m22, matrix.m23),
        simd_make_float4(matrix.m30, matrix.m31, matrix.m32, matrix.m33),
    };
    return ret;
}

- (void)setupMatrixWithEncoder:(id<MTLRenderCommandEncoder>)renderEncoder {
    CGSize size = self.vc.view.bounds.size;
    float aspect = fabs(size.width / size.height);
    GLKMatrix4 projectionMatrix = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(90.0), aspect, 0.1f, 10.f);
    GLKMatrix4 modelViewMatrix = GLKMatrix4Translate(GLKMatrix4Identity, 0.0f, 0.0f, -2.0f);
    static float x = 0.0, y = 0.0, z = M_PI;
    //    if (self.mRotationXSwitch.on) {
    //        x += self.mSlider.value;
    //    }
    //    if (self.mRotationYSwitch.on) {
    //        y += self.mSlider.value;
    //    }
    //    if (self.mRotationZSwitch.on) {
    //        z += self.mSlider.value;
    //    }
    x += 0.1;
    
    modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, x, 1, 0, 0);
    modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, y, 0, 1, 0);
    modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, z, 0, 0, 1);
    
    GMatrix matrix = {[self getMetalMatrixFromGLKMatrix:projectionMatrix], [self getMetalMatrixFromGLKMatrix:modelViewMatrix]};
    
    [renderEncoder setVertexBytes:&matrix
                           length:sizeof(matrix)
                          atIndex:GVertexInputIndexMatrix];
}

#pragma mark - delegate

- (void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size {
    self.viewportSize = (vector_uint2){size.width, size.height};
}

- (void)drawInMTKView:(MTKView *)view {
    
    id<MTLCommandBuffer> commandBuffer = [self.commandQueue commandBuffer];
    MTLRenderPassDescriptor *renderPassDescriptor = view.currentRenderPassDescriptor;
    
    if(renderPassDescriptor != nil)
    {
        renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(0.0, 0.5, 0.5, 1.0f);
        renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
        
        id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
        
        [renderEncoder setViewport:(MTLViewport){0.0, 0.0, self.viewportSize.x, self.viewportSize.y, -1.0, 1.0 }];
        
        [renderEncoder setFrontFacingWinding:MTLWindingCounterClockwise];
//        [renderEncoder setCullMode:MTLCullModeBack];
        [renderEncoder setRenderPipelineState:self.pipelineState];
        [self setupMatrixWithEncoder:renderEncoder];
        
        [renderEncoder setVertexBuffer:self.vertices
                                offset:0
                               atIndex:GVertexInputIndexVertices];
    
        
        [renderEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle
                                  indexCount:self.indexCount
                                   indexType:MTLIndexTypeUInt32
                                 indexBuffer:self.indexs
                           indexBufferOffset:0];
        
        [renderEncoder endEncoding];
        
        [commandBuffer presentDrawable:view.currentDrawable];
    }
    
    [commandBuffer commit];
}

@end
