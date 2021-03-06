# ANE-Bugsee

Adobe AIR native extension for the bug and crash reporting platform [Bugsee](https://www.bugsee.com).

### Bugsee SDK versions

* iOS `v1.25.5` (Apr 7, 2020)

### Getting Started

Download the ANE from the [releases](../../releases/) page and add it to your app's descriptor:

```xml
<extensions>
    <extensionID>com.digitalstrawberry.ane.bugsee</extensionID>
</extensions>
```

### Usage

#### Initialization

In some cases it makes sense to enable Bugsee on builds distributed through TestFlight but keep it disabled on the ones distributed through iTunes. You can check if the current build is running in TestFlight:

```as3
if(Bugsee.instance.isTestFlight)
{
    // We are in TestFlight
}
```

Initialize the Bugsee SDK when you need to by providing your Bugsee app id and optionally a set of options. See the [official documentation](https://docs.bugsee.com/sdk/ios/configuration/#available-options) and the [BugseeOptions class](actionscript/common/src/com/digitalstrawberry/ane/bugsee/BugseeOptions.as) for the list of available options.

```as3
var options:Object = {};
options[BugseeOptions.KillDetectionKey] = true;
Bugsee.instance.init("bugsee_app_id", options);
```

#### Logging

Bugsee automatically reports native crashes (unless disabled), but you can report non-fatal errors that occur in your ActionScript code. These reports will get combined similar to crashes, and you will be provided with statistics and a break down by unique devices, IOS versions, etc.

```as3
var errorCode:int = 123;
Bugsee.instance.logError("Error name", errorCode);
```

You can provide custom error data as the last argument:

```as3
Bugsee.instance.logError("Error name", errorCode, { additionalData: "..." });
```

Bugsee also collects console logs and attaches them to each report. Note that ActionScript's `trace()` calls are removed from release builds and do not appear in the bug reports. You need to make use of the `logToConsole` method to have console logs appear in your bug reports:

```as3
Bugsee.instance.logToConsole("Log message");
```

#### Attaching files

Binary files (attachments) can also be added to the report right before report is being sent. The attachment will be available for download right from the issue viewer. Currently both the amount of attachments and their size is limited. Maximum of 3 attachments, 1MB each.

```as3
var file:File = File.applicationDirectory.resolvePath("attachment.txt");
Bugsee.instance.addAttachment("attachment name", "attachment.txt", file.nativePath);
```

#### Session/User attributes

Any arbitrary attributes can be attached to the reports. Issues are searchable by these attributes in the Bugsee dashboard as well.

```as3
Bugsee.instance.setAttribute("uuid", "1337");
Bugsee.instance.setAttribute("name", "John Doe");

Bugsee.instance.clearAttribute("uuid");

Bugsee.instance.clearAttributes();
```

#### Stop / Relaunch

You can stop Bugsee completely using the `stop` method. The recording will be stopped and all the used resources will be cleaned up. Bugsee can be relaunched later by calling the `relaunch` method.

```as3
Bugsee.instance.stop();

...

Bugsee.instance.relaunch(options);
```

#### Show feedback controller

You can show a feedback controller that allows your users to communicate with your support and developers.
Feedback controller:

```as3
Bugsee.instance.showFeedbackController();
```

You can add an event listener to receive feedback messages coming from the server. These messages are only received during initialization and not during a live chat session:

```as3
Bugsee.instance.addEventListener(BugseeEvent.FEEDBACK, feedbackReceived);
Bugsee.instance.init(...);

...

private function feedbackReceived(event:BugseeEvent):void
{
	trace(event.messages);
}
```

Default greeting can be set on the server in your application settings. However, for the cases when network is not available, you can set default greeting on the client as well:

```as3
Bugsee.instance.setDefaultFeedbackGreeting("Hello!");
```