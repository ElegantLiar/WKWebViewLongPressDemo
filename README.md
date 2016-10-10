# WKWebViewLongPressDemo
##思路:WKWebView与JS交互, 获取长按位置图片url, 获取图片资源, 保存到本地相册
###对比UIWebView JS代码执行改变:
#####WKWebView执行完毕假如有返回参数通过completionHandler:Block回调出来
```
- (void)evaluateJavaScript:(NSString *)javaScriptString completionHandler:(void (^ _Nullable)(_Nullable id, NSError * _Nullable error))completionHandler;
```
#####UIWebView执行JS代码直接返回
```
- (nullable NSString *)stringByEvaluatingJavaScriptFromString:(NSString *)script;
```
#####给WKWebView添加手势
```
UILongPressGestureRecognizer *longPress = [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(handleLongPress:)];
longPress.minimumPressDuration = 1;
longPress.delegate = self;
[_webView addGestureRecognizer:longPress];
[self.view addSubview:_webView];
```
##### 屏蔽前端页面自带的长按弹出列表
```
- (void)webView:(WKWebView *)webView didFinishNavigation:(WKNavigation *)navigation{
// 不执行前段界面弹出列表的JS代码
[self.webView evaluateJavaScript:@"document.documentElement.style.webkitTouchCallout='none';" 
```

#####获取长按点击位置对应的图片url (JS交互)
```
- (void)handleLongPress:(UILongPressGestureRecognizer *)sender{
if (sender.state != UIGestureRecognizerStateBegan) {
return;
}
CGPoint touchPoint = [sender locationInView:self.webView];
// 获取长按位置对应的图片url的JS代码
NSString *imgJS = [NSString stringWithFormat:@"document.elementFromPoint(%f, %f).src", touchPoint.x, touchPoint.y];
// 执行对应的JS代码 获取url
[self.webView evaluateJavaScript:imgJS completionHandler:^(id _Nullable imgUrl, NSError * _Nullable error) {
if (imgUrl) {
NSData *data = [NSData dataWithContentsOfURL:[NSURL URLWithString:imgUrl]];
UIImage *image = [UIImage imageWithData:data];
if (!image) {
NSLog(@"读取图片失败");
return;
}
_saveImage = image;
FSActionSheet *actionSheet = nil;
if ([self isAvailableQRcodeIn:image]) {
actionSheet = [[FSActionSheet alloc] initWithTitle:nil
delegate:self
cancelButtonTitle:@"取消"
highlightedButtonTitle:nil
otherButtonTitles:@[@"保存图片", @"打开二维码"]];
} else {
actionSheet = [[FSActionSheet alloc] initWithTitle:nil
delegate:self
cancelButtonTitle:@"取消"
highlightedButtonTitle:nil
otherButtonTitles:@[@"保存图片"]];
}
[actionSheet show];
}
}];
```