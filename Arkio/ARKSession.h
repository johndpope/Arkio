//
//  ARKSession.h
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

#import "ARKContact.h"

@class ARKUser;
@class ARKServer;
@class ARKError;
@class ARKCompany;
@class ARKCompanyStatistics;
@class ARKCompanySearchResult;
@class ARKContactSearchResult;


/**
 *  The `ARKSession` class provides methods for interacting with the Data.com API service on an `ARKServer` for an `ARKUser`.
 */
@interface ARKSession : NSObject

/**
 *  The Data.com user account  incl. authentication credentials to use for API requests to the server.
 */
@property (nonatomic, strong, readonly) ARKUser *user;

/**
 *  The Data.com server instance to which API requests will be sent.
 */
@property (nonatomic, strong, readonly) ARKServer *server;

/**
 *  The Data.com API Developer Token to send with each request.
 */
@property (nonatomic, strong) NSString *APIDeveloperToken;

#pragma mark - Creating and Initializing a User Session
#pragma mark - Designated Object Initializers
///-----------------------------------------------
/// @name Creating and Initializing a User Session
///-----------------------------------------------

/**
 *  Creates an `ARKSession`, initialized with the given Data.com account username and password.
 *
 *  @param username The name of the Data.com account we want to access.
 *  @param password The password associated with the given account username.
 *  @return An `ARKSession` instance initialized with the given account credentials.
 */
- (instancetype)initWithUsername:(NSString *)username password:(NSString *)password;

/**
 *  Creates an `ARKSession`, initialized with the give `ARKUser`.
 *
 *  @param user An `ARKUser` instance.
 *  @return An `ARKSession` instance initialized with the given user account credentials.
 */
- (instancetype)initWithUser:(ARKUser *)user;

/**
 *  Creates an `ARKSession`, initialized with the values stored in `NSUserDefaults`.
 *
 *  Looks for the following keys in `NSUserDefaults`:
 *
 *  - arkio.account.username
 *  - arkio.account.password
 *
 *  @return An `ARKSession` instance initialized with the `NSUserDefaults` user account credentials.
 */
- (instancetype)initWithDefaultUser;

/**
 *  Creates an `ARKSession`, initialized with the given Data.com username and password
 *  and configured to connect to the given `ARKServer`.
 *
 *  @param username The name of the Data.com account we want to access.
 *  @param password The password associated with the given account username.
 *  @param server   An `ARKServer` to connect this `ARKSession` instance to.
 *
 *  @return An `ARKSession` instance initialized with the given account credentials and server.
 */
- (instancetype)initWithUsername:(NSString *)username
                        password:(NSString *)password
                          server:(ARKServer *)server;

/**
 *  Returns an `ARKSession`, initialized with the give `ARKUser` account credentials and `ARKServer`.
 *
 *  @param user An `ARKUser` instance.
 *  @param server  An `ARKServer` to connect this `ARKSession` instance to.
 *
 *  @return An `ARKSession` instance initialized with the given account credentials and server.
 */
- (instancetype)initWithUser:(ARKUser *)user
                      server:(ARKServer *)server;

#pragma mark - User / Authentication Requests

///---------------------------------------
/// @name User and Authentication Requests
///---------------------------------------

/**
 *  Authenticate a session with the Data.com service
 *
 *  @param success A block object to execute when the task finishes succcesfully. This block has no return value and takes two argumenta: a boolean variable indicating whether the user authenticated successfully, and an ARKError object which is not nil if the API returned an application error.
 *  @param failure A block object to execute at the completion of an unsuccessful request. This block has no return value and takes one argument: the error that occured during the request.
 */
- (void)authenticate:(void (^)(BOOL authenticated, ARKError *error))success
             failure:(void (^)(NSError *error))failure;


/**
 *  Requests the user information (account point balance) for the current session user.
 *
 *  @param success A block object to execute when the task finishes succcesfully. This block has no return value and takes two argumenta: a long variable containing the number of points on a user's account balance, and an ARKError object which is not nil if the API returned an application error.
 *  @param failure A block object to execute at the completion of an unsuccessful request. This block has no return value and takes one argument: the error that occured during the request.
 */
- (void)userInformation:(void (^)(long points, ARKError *error))success
                failure:(void (^)(NSError *error))failure;

#pragma mark - Contact Requests

///--------------------------------------
/// @name Contact Search and Get Requests
///--------------------------------------

/**
 *  Requests contacts with an email address or name matching the given string.
 *
 *  @param string The text to apply to the search query.
 *  @param offset A numeric offset which to begin returning results from.
 *  @param size   An `int` containing the number of results to return.
 *  @param success  A block object to execute when the task finishes succcesfully. This block has no return value and takes two arguments: an `ARKCompanySearchResult` object containing the companies from the result set and an ARKError object which is not nil if the API returned an application error.
 *  @param failure A block object to execute at the completion of an unsuccessful request. This block has no return value and takes one argument: the error that occured during the request. 
 */
- (void)searchContactsWithString:(NSString *)string
                          offset:(int)offset
                            size:(int)size
                         success:(void (^)(ARKContactSearchResult *result, ARKError *error))success
                         failure:(void (^)(NSError *error))failure;


/**
 *  Requests contacts matching the given method arguments.
 *
 *  @param companyName The name of the company the contact is employed by.
 *  @param firstLast   The first and last name of a contact.
 *  @param level       The level the contact is employed at.
 *  @param offset      A numeric offset which to begin returning results from.
 *  @param size        An `int` containing the number of results to return.
 *  @param success     A block object to execute when the task finishes succcesfully. This block has no return value and takes two arguments: an `ARKCompanySearchResult` object containing the companies from the result set and an ARKError object which is not nil if the API returned an application error.
 *  @param failure     A block object to execute at the completion of an unsuccessful request. This block has no return value and takes one argument: the error that occured during the request.
 */
- (void)searchContactsWithCompanyName:(NSString *)companyName
                            firstLast:(NSString *)firstLast
                                level:(ARKContactLevel)level
                               offset:(int)offset
                                 size:(int)size
                              success:(void (^)(ARKContactSearchResult *result, ARKError *error))success
                              failure:(void (^)(NSError *error))failure;

/**
 *  Gets a Contact's full data from the Data.com API, as a point spend.
 *
 *  @param contactID the ID of the contact to purchase.
 *  @param success   A block object to execute when the task finishes succcesfully. This block has no return value and takes two arguments: an `ARKContact` object with the contactID requested and an ARKError object which is not nil if the API returned an application error, such as a user not having enough points.
 *  @param failure   A block object to execute at the completion of an unsuccessful request. This block has no return value and takes one argument: the error that occured during the request.
 */
- (void)contactWithID:(long)contactID
              success:(void (^)(ARKContact *contact, ARKError *error))success
              failure:(void (^)(NSError *error))failure;

#pragma mark - Company Requests

///--------------------------------------
/// @name Company Search and Get Requests
///--------------------------------------

/**
 *  Requests the count statistics for a company.
 *
 *  @param companyID The unique identifier of the company we're requesting the count statistics of.
 *  @param success   A block object to execute when the task finishes succcesfully. This block has no return value and takes two argumenta: an `ARKCompanyStatistics` object containing the count statistics, and an ARKError object which is not nil if the API returned an application error.
 *  @param failure   A block object to execute at the completion of an unsuccessful request. This block has no return value and takes one argument: the error that occured during the request.
 */
- (void)statisticsForCompanyID:(long)companyID
                       success:(void (^)(ARKCompanyStatistics *stats, ARKError *error))success
                       failure:(void (^)(NSError *error))failure;


/**
 *  Requests a search for companies who match on the given string.
 *
 *  Search text can match on any of the following Company fields:
 *
 *  - company name
 *  - website domain name
 *  - stock ticker symbol
 *
 *  @param string   The text to apply to the search query.
 *  @param offset   A numeric offset which to begin returning results from.
 *  @param size     An `int` containing the number of results to return.
 *  @param detailed Set to `YES` to have detailed information for each contact, otherwise set to `NO`.
 *  @param success  A block object to execute when the task finishes succcesfully. This block has no return value and takes two arguments: an `ARKCompanySearchResult` object containing the companies from the result set and an ARKError object which is not nil if the API returned an application error.
 *  @param failure A block object to execute at the completion of an unsuccessful request. This block has no return value and takes one argument: the error that occured during the request.
 */
- (void)searchCompaniesWithString:(NSString *)string
                           offset:(int)offset
                             size:(int)size
                         detailed:(BOOL)detailed
                          success:(void (^)(ARKCompanySearchResult *results, ARKError *error))success
                          failure:(void (^)(NSError *error))failure;

@end

extern NSString * const kARKAPIDeveloperTokenKey;
