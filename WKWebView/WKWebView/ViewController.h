//
//  ViewController.h
//  WKWebView
//
//  Created by etouch on 16/10/9.
//  Copyright © 2016年 EL. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WebKit/WebKit.h>
#import "FSActionSheet.h"


@interface ViewController : UIViewController<
WKNavigationDelegate,
WKUIDelegate,
UIGestureRecognizerDelegate,
FSActionSheetDelegate
>

@property (nonatomic, strong) WKWebView *webView;

@end

