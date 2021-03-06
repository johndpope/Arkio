//
//  ARKServer.h
//  Arkio
//
//  Created by Ray Scott on 22/11/2013.
//  Copyright (c) 2013 Alien Hitcher. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <Foundation/Foundation.h>

/**
 *  This class represents a remote Data.com server that provides an application programming interface for clients to connect to. A new `ARKSession` can be connected to the server to allow access to the account of an `ARKUser`.
 */
@interface ARKServer : NSObject

/**
 *  The host name of the server.
 */
@property (nonatomic, strong, readonly) NSURL *host;

/**
 *  A string containing the path for the host at which the API service endpoint can be found.
 *
 *  The host plus the path will give you the service endpoint.
 */
@property (nonatomic, strong, readonly) NSString *path;

/**
 *  The URL representing the API service endpoint.
 *
 *  If a server instance is created by specifying a host name and path, using either the `initWithHost:path:` method or using the related configuration keys in the app's `Info.plist` file then the endpoint URL is derived dynamically from these two values.
 */
@property (nonatomic, strong, readonly) NSURL *endpoint;

#pragma mark - Designated Object Initializers

///------------------------------------------
///  @name Creating and Initializing a Server
///------------------------------------------

/**
 *  Creates a server object initializing it with properties found in the apps main bundle.
 *
 *  This method looks for the following keys in the app's `Info.plist` file:
 *
 *  - `"arkio.api.host"`
 *  - `"arkio.api.path"`
 *  - `"arkio.api.url"`
 *
 *  #### How Configuration Values Are Resolved
 *  A detailed configuration takes precendence over a more general one.
 *
 *  1. This method first looks for a host value using the `"arkio.api.host"` key. If it is found it then looks for a path value using the `"arkio.api.path"` key and appends this value to the host name to form the API endpoint URL. If a path value is not found, it simply uses the host name as the endpoint.
 *  2. If a host name isn't found, this method then looks for the endpoint URL using the key `"arkio.api.url"`. If one is found, this value is used as the API endpoint.
 *  3. If no keys are found in the app's `Info.plist` file, then the default `kArkioApiDefaultEndpoint` endpoint is used.
 *  @return An `ARKServer` instance initialized from the apps `Info.plist` file in the main bundle.
 */
+ (instancetype)mainBundleServer;

/**
 *  Creates a server object with the given host URL and path string.
 *
 *  @param host The URL of a Data.com API host
 *  @param path A string containing the path to the API endpoint in the given host.
 *
 *  @return An `ARKServer` instance initialized with the given host name and path.
 */
- (instancetype)initWithHost:(NSURL *)host path:(NSString *)path;

/**
 *  Creates a server object with the given API endpoint URL.
 *
 *  @param endpoint A URL with a complete path pointing to the Data.com API service.
 *
 *  @return An `ARKServer` instance initialized with the given endpoint URL.
 */
- (instancetype)initWithAPIEndpoint:(NSURL *)endpoint;


@end

extern NSString  * const kArkioApiHostKey;
extern NSString  * const kArkioApiPathKey;
extern NSString  * const kArkioApiUrlKey;
extern NSString  * const kArkioApiDefaultEndpoint;