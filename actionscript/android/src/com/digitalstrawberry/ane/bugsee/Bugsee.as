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

	public class Bugsee extends EventDispatcher implements IBugsee
	{

		/* Singleton stuff */
		private static var mCanInitialize:Boolean;
		private static var mInstance:IBugsee;


		/**
		 * @private
		 */
		public function Bugsee()
		{
			if(!mCanInitialize)
			{
				throw new Error("Bugsee is a singleton, use instance getter.");
			}
		}


		public static function get instance():IBugsee
		{
			if(!mInstance)
			{
				mCanInitialize = true;
				mInstance = new Bugsee();
				mCanInitialize = false;
			}
			return mInstance;
		}


		public function init(appToken:String, options:Object = null):void
		{
		}


		public function relaunch(options:Object = null):void
		{

		}


		public function logError(name:String, code:int = -1, params:Object = null):void
		{
		}


		public function logEvent(name:String, params:Object = null):void
		{
		}


		public function logToConsole(message:String):void
		{

		}


		public function addAttachment(name:String, fileName:String, filePath:String):void
		{
		}


		public function setAttribute(key:String, value:String):void
		{
		}


		public function clearAttribute(key:String):void
		{
		}


		public function clearAttributes():void
		{
		}
		
		
		public function stop():void
		{
			
		}


		public function dispose():void
		{
		}


		public function get isTestFlight():Boolean
		{
			return false;
		}


		public function get isSupported():Boolean
		{
			return false;
		}
	}
}
