//
//  NSObject+ARKFoundation.m
//  Arkio
//
//  Created by Ray Scott on 05/12/2013.
//  Copyright (c) 2013 Alien Hitcher. All rights reserved.
//

#import "NSObject+ARKFoundation.h"
#import <objc/runtime.h>

@implementation NSObject (ARKFoundation)

- (NSString *) autoDescriptionForClassType:(Class)classType {
    
	NSMutableString * result = [NSMutableString string];
    
	// Find Out something about super Classes
	Class superClass  = class_getSuperclass(classType);
	if  ( superClass != nil && ![superClass isEqual:[NSObject class]])
	{
		// Append all the super class's properties to the result (Reqursive, until NSObject)
		[result appendString:[self autoDescriptionForClassType:superClass]];
	}
    
	// Add Information about Current Properties
	u_int property_count;
	objc_property_t * property_list = class_copyPropertyList(classType, &property_count); // Must Free, later
    
	for (int i = 0; i < property_count; i++) { // Reverse order, to get Properties in order they were defined
		objc_property_t property = property_list[i];
        
		// For Eeach property we are loading its name
		const char * property_name = property_getName(property);
        
		NSString * propertyName = [NSString stringWithCString:property_name encoding:NSASCIIStringEncoding];
		if (propertyName) { // and if name is ok, we are getting value using KVC
			id value = [self valueForKey:propertyName];
            
			// format of result items: p1 = v1; p2 = v2; ...
            [result appendFormat:@"\t%@ = ", propertyName];
            
            if ([value isKindOfClass:[NSString class]]) {
                [result appendFormat:@"\"%@\";\n", value];
            }
            else {
                [result appendFormat:@"%@;\n", value];
            }
			
            
            
		}
	}
	free(property_list);//Clean up
    
	return result;
}

// Reflects about self.
- (NSString *) autoDescription {
	return [NSString stringWithFormat:@"[%@ {\n%@}]", NSStringFromClass([self class]), [self autoDescriptionForClassType:[self class]]];
}

@end
