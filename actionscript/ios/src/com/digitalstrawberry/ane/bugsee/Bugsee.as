/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Digital Strawberry LLC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.digitalstrawberry.ane.bugsee
{

	import flash.events.EventDispatcher;
	import flash.events.StatusEvent;
	import flash.external.ExtensionContext;

	public class Bugsee extends EventDispatcher implements IBugsee
	{

		private static const TAG:String = "[Bugsee]";
		private static const EXTENSION_ID:String = "com.digitalstrawberry.ane.bugsee";

		private static var _context:ExtensionContext;

		/* Event codes */

		/* Singleton stuff */
		private static var sCanInitialize:Boolean;
		private static var sInstance:IBugsee;


		/**
		 * @private
		 */
		public function Bugsee()
		{
			if(!sCanInitialize)
			{
				throw new Error("Bugsee is a singleton, use instance getter.");
			}

			if(!initExtensionContext())
			{
				log("Error creating extension context for " + EXTENSION_ID);
				return;
			}
		}


		public static function get instance():IBugsee
		{
			if(!sInstance)
			{
				sCanInitialize = true;
				sInstance = new Bugsee();
				sCanInitialize = false;
			}
			return sInstance;
		}


		//
		// Public API
		//


		public function init(appToken:String, options:Object = null):void
		{
			_context.call("init", appToken, (options == null) ? null : JSON.stringify(options));
		}


		public function logError(name:String, code:int = -1, params:Object = null):void
		{
			_context.call("logError", name, code, (params == null) ? null : JSON.stringify(params));
		}


		public function logEvent(name:String, params:Object = null):void
		{
			_context.call("logEvent", name, (params == null) ? null : JSON.stringify(params));
		}


		public function logToConsole(message:String):void
		{
			_context.call("logToConsole", message);
		}


		public function addAttachment(name:String, fileName:String, filePath:String):void
		{
			_context.call("addAttachment", name, fileName, filePath);
		}


		public function setAttribute(key:String, value:String):void
		{
			_context.call("setAttribute", key, value);
		}


		public function clearAttribute(key:String):void
		{
			_context.call("clearAttribute", key);
		}


		public function clearAttributes():void
		{
			_context.call("clearAttributes");
		}


		public function stop():void
		{
			_context.call("stop");
		}


		public function dispose():void
		{
			if(_context == null)
			{
				return;
			}

			_context.dispose();
			_context = null;
		}


		public function get isTestFlight():Boolean
		{
			return _context.call("isTestFlight") as Boolean;
		}


		public function get isSupported():Boolean
		{
			return true;
		}


		//
		// Private API
		//


		/**
		 * Initializes extension context.
		 * @return <code>true</code> if initialized successfully, <code>false</code> otherwise.
		 */
		private static function initExtensionContext():Boolean
		{
			if(_context === null)
			{
				try
				{
					_context = ExtensionContext.createExtensionContext(EXTENSION_ID, null);
				}
				catch(e:Error)
				{
				}
			}
			return _context !== null;
		}


		private static function log(message:String):void
		{
			trace(TAG, message);
		}

	}
}
