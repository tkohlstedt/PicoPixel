#define jscolor_script "/**\n"\
" * jscolor - JavaScript Color Picker\n"\
" *\n"\
" * @link    http://jscolor.com\n"\
" * @license For open source use: GPLv3\n"\
" *          For commercial use: JSColor Commercial License\n"\
" * @author  Jan Odvarko - East Desire\n"\
" * @version 2.4.8\n"\
" *\n"\
" * See usage examples at http://jscolor.com/examples/\n"\
" */\n"\
"(function (global, factory) {\n"\
"	'use strict';\n"\
"	if (typeof module === 'object' && typeof module.exports === 'object') {\n"\
"		// Export jscolor as a module\n"\
"		module.exports = global.document ?\n"\
"			factory (global) :\n"\
"			function (win) {\n"\
"				if (!win.document) {\n"\
"					throw new Error('jscolor needs a window with document');\n"\
"				}\n"\
"				return factory(win);\n"\
"			}\n"\
"		return;\n"\
"	}\n"\
"	// Default use (no module export)\n"\
"	factory(global);\n"\
"})(typeof window !== 'undefined' ? window : this, function (window) { // BEGIN factory\n"\
"// BEGIN jscolor code\n"\
"'use strict';\n"\
"var jscolor = (function () { // BEGIN jscolor\n"\
"var jsc = {\n"\
"	initialized : false,\n"\
"	instances : [], // created instances of jscolor\n"\
"	readyQueue : [], // functions waiting to be called after init\n"\
"	register : function () {\n"\
"		if (typeof window !== 'undefined' && window.document) {\n"\
"			window.document.addEventListener('DOMContentLoaded', jsc.pub.init, false);\n"\
"		}\n"\
"	},\n"\
"	installBySelector : function (selector, rootNode) {\n"\
"		rootNode = rootNode ? jsc.node(rootNode) : window.document;\n"\
"		if (!rootNode) {\n"\
"			throw new Error('Missing root node');\n"\
"		}\n"\
"		var elms = rootNode.querySelectorAll(selector);\n"\
"		// for backward compatibility with DEPRECATED installation/configuration using className\n"\
"		var matchClass = new RegExp('(^|\\s)(' + jsc.pub.lookupClass + ')(\\s*(\\{[^}]*\\})|\\s|$)', 'i');\n"\
"		for (var i = 0; i < elms.length; i += 1) {\n"\
"			if (elms[i].jscolor && elms[i].jscolor instanceof jsc.pub) {\n"\
"				continue; // jscolor already installed on this element\n"\
"			}\n"\
"			if (elms[i].type !== undefined && elms[i].type.toLowerCase() == 'color' && jsc.isColorAttrSupported) {\n"\
"				continue; // skips inputs of type 'color' if supported by the browser\n"\
"			}\n"\
"			var dataOpts, m;\n"\
"			if (\n"\
"				(dataOpts = jsc.getDataAttr(elms[i], 'jscolor')) !== null ||\n"\
"				(elms[i].className && (m = elms[i].className.match(matchClass))) // installation using className (DEPRECATED)\n"\
"			) {\n"\
"				var targetElm = elms[i];\n"\
"				var optsStr = '';\n"\
"				if (dataOpts !== null) {\n"\
"					optsStr = dataOpts;\n"\
"				} else if (m) { // installation using className (DEPRECATED)\n"\
"					console.warn('Installation using class name is DEPRECATED. Use data-jscolor="" attribute instead.' + jsc.docsRef);\n"\
"					if (m[4]) {\n"\
"						optsStr = m[4];\n"\
"					}\n"\
"				}\n"\
"				var opts = null;\n"\
"				if (optsStr.trim()) {\n"\
"					try {\n"\
"						opts = jsc.parseOptionsStr(optsStr);\n"\
"					} catch (e) {\n"\
"						console.warn(e + '\\n' + optsStr);\n"\
"					}\n"\
"				}\n"\
"				try {\n"\
"					new jsc.pub(targetElm, opts);\n"\
"				} catch (e) {\n"\
"					console.warn(e);\n"\
"				}\n"\
"			}\n"\
"		}\n"\
"	},\n"\
"	parseOptionsStr : function (str) {\n"\
"		var opts = null;\n"\
"		try {\n"\
"			opts = JSON.parse(str);\n"\
"		} catch (eParse) {\n"\
"			if (!jsc.pub.looseJSON) {\n"\
"				throw new Error('Could not parse jscolor options as JSON: ' + eParse);\n"\
"			} else {\n"\
"				// loose JSON syntax is enabled -> try to evaluate the options string as JavaScript object\n"\
"				try {\n"\
"					opts = (new Function ('var opts = (' + str + '); return typeof opts === \"object\" ? opts : {};'))();\n"\
"				} catch (eEval) {\n"\
"					throw new Error('Could not evaluate jscolor options: ' + eEval);\n"\
"				}\n"\
"			}\n"\
"		}\n"\
"		return opts;\n"\
"	},\n"\
"	getInstances : function () {\n"\
"		var inst = [];\n"\
"		for (var i = 0; i < jsc.instances.length; i += 1) {\n"\
"			// if the targetElement still exists, the instance is considered 'alive' \n"\
"           if (jsc.instances[i] && jsc.instances[i].targetElement) {\n"\
"				inst.push(jsc.instances[i]);\n"\
"			}\n"\
"		}\n"\
"		return inst;\n"\
"	},\n"\
"	createEl : function (tagName) {\n"\
"		var el = window.document.createElement(tagName);\n"\
"		jsc.setData(el, 'gui', true);\n"\
"		return el;\n"\
"	},\n"\
"	node : function (nodeOrSelector) {\n"\
"		if (!nodeOrSelector) {\n"\
"			return null;\n"\
"		}\n"\
"		if (typeof nodeOrSelector === 'string') {\n"\
"			// query selector\n"\
"			var sel = nodeOrSelector;\n"\
"			var el = null;\n"\
"			try {\n"\
"				el = window.document.querySelector(sel);\n"\
"			} catch (e) {\n"\
"				console.warn(e);\n"\
"				return null;\n"\
"			}\n"\
"			if (!el) {\n"\
"				console.warn('No element matches the selector: %s', sel);\n"\
"			}\n"\
"			return el;\n"\
"		}\n"\
"		if (jsc.isNode(nodeOrSelector)) {\n"\
"			// DOM node\n"\
"			return nodeOrSelector;\n"\
"		}\n"\
"		console.warn('Invalid node of type %s: %s', typeof nodeOrSelector, nodeOrSelector);\n"\
"		return null;\n"\
"	},\n"\
"	// See https://stackoverflow.com/questions/384286/\n"\
"	isNode : function (val) {\n"\
"		if (typeof Node === 'object') {\n"\
"			return val instanceof Node;\n"\
"		}\n"\
"		return val && typeof val === 'object' && typeof val.nodeType === 'number' && typeof val.nodeName === 'string';\n"\
"	},\n"\
"	nodeName : function (node) {\n"\
"		if (node && node.nodeName) {\n"\
"			return node.nodeName.toLowerCase();\n"\
"		}\n"\
"		return false;\n"\
"	},\n"\
"	removeChildren : function (node) {\n"\
"		while (node.firstChild) {\n"\
"			node.removeChild(node.firstChild);\n"\
"		}\n"\
"	},\n"\
"	isTextInput : function (el) {\n"\
"		return el && jsc.nodeName(el) === 'input' && el.type.toLowerCase() === 'text';\n"\
"	},\n"\
"	isButton : function (el) {\n"\
"		if (!el) {\n"\
"			return false;\n"\
"		}\n"\
"		var n = jsc.nodeName(el);\n"\
"		return (\n"\
"			(n === 'button') ||\n"\
"			(n === 'input' && ['button', 'submit', 'reset'].indexOf(el.type.toLowerCase()) > -1)\n"\
"		);\n"\
"	},\n"\
"	isButtonEmpty : function (el) {\n"\
"		switch (jsc.nodeName(el)) {\n"\
"			case 'input': return (!el.value || el.value.trim() === '');\n"\
"			case 'button': return (el.textContent.trim() === '');\n"\
"		}\n"\
"		return null; // could not determine element's text\n"\
"	},\n"\
"	// See https://github.com/WICG/EventListenerOptions/blob/gh-pages/explainer.md\n"\
"	isPassiveEventSupported : (function () {\n"\
"		var supported = false;\n"\
"		try {\n"\
"			var opts = Object.defineProperty({}, 'passive', {\n"\
"				get: function () { supported = true; }\n"\
"			});\n"\
"			window.addEventListener('testPassive', null, opts);\n"\
"			window.removeEventListener('testPassive', null, opts);\n"\
"		} catch (e) {}\n"\
"		return supported;\n"\
"	})(),\n"\
"	isColorAttrSupported : (function () {\n"\
"		var elm = window.document.createElement('input');\n"\
"		if (elm.setAttribute) {\n"\
"			elm.setAttribute('type', 'color');\n"\
"			if (elm.type.toLowerCase() == 'color') {\n"\
"				return true;\n"\
"			}\n"\
"		}\n"\
"		return false;\n"\
"	})(),\n"\
"	dataProp : '_data_jscolor',\n"\
"	// usage:\n"\
"	//   setData(obj, prop, value)\n"\
"	//   setData(obj, {prop:value, ...})\n"\
"	//\n"\
"	setData : function () {\n"\
"		var obj = arguments[0];\n"\
"		if (arguments.length === 3) {\n"\
"			// setting a single property\n"\
"			var data = obj.hasOwnProperty(jsc.dataProp) ? obj[jsc.dataProp] : (obj[jsc.dataProp] = {});\n"\
"			var prop = arguments[1];\n"\
"			var value = arguments[2];\n"\
"			data[prop] = value;\n"\
"			return true;\n"\
"		} else if (arguments.length === 2 && typeof arguments[1] === 'object') {\n"\
"			// setting multiple properties\n"\
"			var data = obj.hasOwnProperty(jsc.dataProp) ? obj[jsc.dataProp] : (obj[jsc.dataProp] = {});\n"\
"			var map = arguments[1];\n"\
"			for (var prop in map) {\n"\
"				if (map.hasOwnProperty(prop)) {\n"\
"					data[prop] = map[prop];\n"\
"				}\n"\
"			}\n"\
"			return true;\n"\
"		}\n"\
"		throw new Error('Invalid arguments');\n"\
"	},\n"\
"	// usage:\n"\
"	//   removeData(obj, prop, [prop...])\n"\
"	//\n"\
"	removeData : function () {\n"\
"		var obj = arguments[0];\n"\
"		if (!obj.hasOwnProperty(jsc.dataProp)) {\n"\
"			return true; // data object does not exist\n"\
"		}\n"\
"		for (var i = 1; i < arguments.length; i += 1) {\n"\
"			var prop = arguments[i];\n"\
"			delete obj[jsc.dataProp][prop];\n"\
"		}\n"\
"		return true;\n"\
"	},\n"\
"	getData : function (obj, prop, setDefault) {\n"\
"		if (!obj.hasOwnProperty(jsc.dataProp)) {\n"\
"			// data object does not exist\n"\
"			if (setDefault !== undefined) {\n"\
"				obj[jsc.dataProp] = {}; // create data object\n"\
"			} else {\n"\
"				return undefined; // no value to return\n"\
"			}\n"\
"		}\n"\
"		var data = obj[jsc.dataProp];\n"\
"		if (!data.hasOwnProperty(prop) && setDefault !== undefined) {\n"\
"			data[prop] = setDefault;\n"\
"		}\n"\
"		return data[prop];\n"\
"	},\n"\
"	getDataAttr : function (el, name) {\n"\
"		var attrName = 'data-' + name;\n"\
"		var attrValue = el.getAttribute(attrName);\n"\
"		return attrValue;\n"\
"	},\n"\
"	setDataAttr : function (el, name, value) {\n"\
"		var attrName = 'data-' + name;\n"\
"		el.setAttribute(attrName, value);\n"\
"	},\n"\
"	_attachedGroupEvents : {},\n"\
"	attachGroupEvent : function (groupName, el, evnt, func) {\n"\
"		if (!jsc._attachedGroupEvents.hasOwnProperty(groupName)) {\n"\
"			jsc._attachedGroupEvents[groupName] = [];\n"\
"		}\n"\
"		jsc._attachedGroupEvents[groupName].push([el, evnt, func]);\n"\
"		el.addEventListener(evnt, func, false);\n"\
"	},\n"\
"	detachGroupEvents : function (groupName) {\n"\
"		if (jsc._attachedGroupEvents.hasOwnProperty(groupName)) {\n"\
"			for (var i = 0; i < jsc._attachedGroupEvents[groupName].length; i += 1) {\n"\
"				var evt = jsc._attachedGroupEvents[groupName][i];\n"\
"				evt[0].removeEventListener(evt[1], evt[2], false);\n"\
"			}\n"\
"			delete jsc._attachedGroupEvents[groupName];\n"\
"		}\n"\
"	},\n"\
"	preventDefault : function (e) {\n"\
"		if (e.preventDefault) { e.preventDefault(); }\n"\
"		e.returnValue = false;\n"\
"	},\n"\
"	triggerEvent : function (el, eventName, bubbles, cancelable) {\n"\
"		if (!el) {\n"\
"			return;\n"\
"		}\n"\
"		var ev = null;\n"\
"		if (typeof Event === 'function') {\n"\
"			ev = new Event(eventName, {\n"\
"				bubbles: bubbles,\n"\
"				cancelable: cancelable\n"\
"			});\n"\
"		} else {\n"\
"			// IE\n"\
"			ev = window.document.createEvent('Event');\n"\
"			ev.initEvent(eventName, bubbles, cancelable);\n"\
"		}\n"\
"		if (!ev) {\n"\
"			return false;\n"\
"		}\n"\
"		// so that we know that the event was triggered internally\n"\
"		jsc.setData(ev, 'internal', true);\n"\
"		el.dispatchEvent(ev);\n"\
"		return true;\n"\
"	},\n"\
"	triggerInputEvent : function (el, eventName, bubbles, cancelable) {\n"\
"		if (!el) {\n"\
"			return;\n"\
"		}\n"\
"		if (jsc.isTextInput(el)) {\n"\
"			jsc.triggerEvent(el, eventName, bubbles, cancelable);\n"\
"		}\n"\
"	},\n"\
"	eventKey : function (ev) {\n"\
"		var keys = {\n"\
"			9: 'Tab',\n"\
"			13: 'Enter',\n"\
"			27: 'Escape',\n"\
"		};\n"\
"		if (typeof ev.code === 'string') {\n"\
"			return ev.code;\n"\
"		} else if (ev.keyCode !== undefined && keys.hasOwnProperty(ev.keyCode)) {\n"\
"			return keys[ev.keyCode];\n"\
"		}\n"\
"		return null;\n"\
"	},\n"\
"	strList : function (str) {\n"\
"		if (!str) {\n"\
"			return [];\n"\
"		}\n"\
"		return str.replace(/^\\s+|\\s+$/g, '').split(/\\s+/);\n"\
"	},\n"\
"	// The className parameter (str) can only contain a single class name\n"\
"	hasClass : function (elm, className) {\n"\
"		if (!className) {\n"\
"			return false;\n"\
"		}\n"\
"		if (elm.classList !== undefined) {\n"\
"			return elm.classList.contains(className);\n"\
"		}\n"\
"		// polyfill\n"\
"		return -1 != (' ' + elm.className.replace(/\\s+/g, ' ') + ' ').indexOf(' ' + className + ' ');\n"\
"	},\n"\
"	// The className parameter (str) can contain multiple class names separated by whitespace\n"\
"	addClass : function (elm, className) {\n"\
"		var classNames = jsc.strList(className);\n"\
"		if (elm.classList !== undefined) {\n"\
"			for (var i = 0; i < classNames.length; i += 1) {\n"\
"				elm.classList.add(classNames[i]);\n"\
"			}\n"\
"			return;\n"\
"		}\n"\
"		// polyfill\n"\
"		for (var i = 0; i < classNames.length; i += 1) {\n"\
"			if (!jsc.hasClass(elm, classNames[i])) {\n"\
"				elm.className += (elm.className ? ' ' : '') + classNames[i];\n"\
"			}\n"\
"		}\n"\
"	},\n"\
"	// The className parameter (str) can contain multiple class names separated by whitespace\n"\
"	removeClass : function (elm, className) {\n"\
"		var classNames = jsc.strList(className);\n"\
"		if (elm.classList !== undefined) {\n"\
"			for (var i = 0; i < classNames.length; i += 1) {\n"\
"				elm.classList.remove(classNames[i]);\n"\
"			}\n"\
"			return;\n"\
"		}\n"\
"		// polyfill\n"\
"		for (var i = 0; i < classNames.length; i += 1) {\n"\
"			var repl = new RegExp(\n"\
"				'^\\s*' + classNames[i] + '\\s*|' +\n"\
"				'\\s*' + classNames[i] + '\\s*$|' +\n"\
"				'\\s+' + classNames[i] + '(\\s+)',\n"\
"				'g'\n"\
"			);\n"\
"			elm.className = elm.className.replace(repl, '$1');\n"\
"		}\n"\
"	},\n"\
"	getCompStyle : function (elm) {\n"\
"		var compStyle = window.getComputedStyle ? window.getComputedStyle(elm) : elm.currentStyle;\n"\
"		// Note: In Firefox, getComputedStyle returns null in a hidden iframe,\n"\
"		// that's why we need to check if the returned value is non-empty\n"\
"		if (!compStyle) {\n"\
"			return {};\n"\
"		}\n"\
"		return compStyle;\n"\
"	},\n"\
"	// Note:\n"\
"	//   Setting a property to NULL reverts it to the state before it was first set\n"\
"	//   with the 'reversible' flag enabled\n"\
"	//\n"\
"	setStyle : function (elm, styles, important, reversible) {\n"\
"		// using '' for standard priority (IE10 apparently doesn't like value undefined)\n"\
"		var priority = important ? 'important' : '';\n"\
"		var origStyle = null;\n"\
"		for (var prop in styles) {\n"\
"			if (styles.hasOwnProperty(prop)) {\n"\
"				var setVal = null;\n"\
"				if (styles[prop] === null) {\n"\
"					// reverting a property value\n"\
"					if (!origStyle) {\n"\
"						// get the original style object, but dont't try to create it if it doesn't exist\n"\
"						origStyle = jsc.getData(elm, 'origStyle');\n"\
"					}\n"\
"					if (origStyle && origStyle.hasOwnProperty(prop)) {\n"\
"						// we have property's original value -> use it\n"\
"						setVal = origStyle[prop];\n"\
"					}\n"\
"				} else {\n"\
"					// setting a property value\n"\
"					if (reversible) {\n"\
"						if (!origStyle) {\n"\
"							// get the original style object and if it doesn't exist, create it\n"\
"							origStyle = jsc.getData(elm, 'origStyle', {});\n"\
"						}\n"\
"						if (!origStyle.hasOwnProperty(prop)) {\n"\
"							// original property value not yet stored -> store it\n"\
"							origStyle[prop] = elm.style[prop];\n"\
"						}\n"\
"					}\n"\
"					setVal = styles[prop];\n"\
"				}\n"\
"				if (setVal !== null) {\n"\
"					elm.style.setProperty(prop, setVal, priority);\n"\
"				}\n"\
"			}\n"\
"		}\n"\
"	},\n"\
"	hexColor : function (r, g, b) {\n"\
"		return '#' + (\n"\
"			('0' + Math.round(r).toString(16)).slice(-2) +\n"\
"			('0' + Math.round(g).toString(16)).slice(-2) +\n"\
"			('0' + Math.round(b).toString(16)).slice(-2)\n"\
"		).toUpperCase();\n"\
"	},\n"\
"	hexaColor : function (r, g, b, a) {\n"\
"		return '#' + (\n"\
"			('0' + Math.round(r).toString(16)).slice(-2) +\n"\
"			('0' + Math.round(g).toString(16)).slice(-2) +\n"\
"			('0' + Math.round(b).toString(16)).slice(-2) +\n"\
"			('0' + Math.round(a * 255).toString(16)).slice(-2)\n"\
"		).toUpperCase();\n"\
"	},\n"\
"	rgbColor : function (r, g, b) {\n"\
"		return 'rgb(' +\n"\
"			Math.round(r) + ',' +\n"\
"			Math.round(g) + ',' +\n"\
"			Math.round(b) +\n"\
"		')';\n"\
"	},\n"\
"	rgbaColor : function (r, g, b, a) {\n"\
"		return 'rgba(' +\n"\
"			Math.round(r) + ',' +\n"\
"			Math.round(g) + ',' +\n"\
"			Math.round(b) + ',' +\n"\
"			(Math.round((a===undefined || a===null ? 1 : a) * 100) / 100) +\n"\
"		')';\n"\
"	},\n"\
"	linearGradient : (function () {\n"\
"		function getFuncName () {\n"\
"			var stdName = 'linear-gradient';\n"\
"			var prefixes = ['', '-webkit-', '-moz-', '-o-', '-ms-'];\n"\
"			var helper = window.document.createElement('div');\n"\
"			for (var i = 0; i < prefixes.length; i += 1) {\n"\
"				var tryFunc = prefixes[i] + stdName;\n"\
"				var tryVal = tryFunc + '(to right, rgba(0,0,0,0), rgba(0,0,0,0))';\n"\
"				helper.style.background = tryVal;\n"\
"				if (helper.style.background) { // CSS background successfully set -> function name is supported\n"\
"					return tryFunc;\n"\
"				}\n"\
"			}\n"\
"			return stdName; // fallback to standard 'linear-gradient' without vendor prefix\n"\
"		}\n"\
"		var funcName = getFuncName();\n"\
"		return function () {\n"\
"			return funcName + '(' + Array.prototype.join.call(arguments, ', ') + ')';\n"\
"		};\n"\
"	})(),\n"\
"	setBorderRadius : function (elm, value) {\n"\
"		jsc.setStyle(elm, {'border-radius' : value || '0'});\n"\
"	},\n"\
"	setBoxShadow : function (elm, value) {\n"\
"		jsc.setStyle(elm, {'box-shadow': value || 'none'});\n"\
"	},\n"\
"	getElementPos : function (e, relativeToViewport) {\n"\
"		var x=0, y=0;\n"\
"		var rect = e.getBoundingClientRect();\n"\
"		x = rect.left;\n"\
"		y = rect.top;\n"\
"		if (!relativeToViewport) {\n"\
"			var viewPos = jsc.getViewPos();\n"\
"			x += viewPos[0];\n"\
"			y += viewPos[1];\n"\
"		}\n"\
"		return [x, y];\n"\
"	},\n"\
"	getElementSize : function (e) {\n"\
"		return [e.offsetWidth, e.offsetHeight];\n"\
"	},\n"\
"	// get pointer's X/Y coordinates relative to viewport\n"\
"	getAbsPointerPos : function (e) {\n"\
"		var x = 0, y = 0;\n"\
"		if (typeof e.changedTouches !== 'undefined' && e.changedTouches.length) {\n"\
"			// touch devices\n"\
"			x = e.changedTouches[0].clientX;\n"\
"			y = e.changedTouches[0].clientY;\n"\
"		} else if (typeof e.clientX === 'number') {\n"\
"			x = e.clientX;\n"\
"			y = e.clientY;\n"\
"		}\n"\
"		return { x: x, y: y };\n"\
"	},\n"\
"	// get pointer's X/Y coordinates relative to target element\n"\
"	getRelPointerPos : function (e) {\n"\
"		var target = e.target || e.srcElement;\n"\
"		var targetRect = target.getBoundingClientRect();\n"\
"		var x = 0, y = 0;\n"\
"		var clientX = 0, clientY = 0;\n"\
"		if (typeof e.changedTouches !== 'undefined' && e.changedTouches.length) {\n"\
"			// touch devices\n"\
"			clientX = e.changedTouches[0].clientX;\n"\
"			clientY = e.changedTouches[0].clientY;\n"\
"		} else if (typeof e.clientX === 'number') {\n"\
"			clientX = e.clientX;\n"\
"			clientY = e.clientY;\n"\
"		}\n"\
"		x = clientX - targetRect.left;\n"\
"		y = clientY - targetRect.top;\n"\
"		return { x: x, y: y };\n"\
"	},\n"\
"	getViewPos : function () {\n"\
"		var doc = window.document.documentElement;\n"\
"		return [\n"\
"			(window.pageXOffset || doc.scrollLeft) - (doc.clientLeft || 0),\n"\
"			(window.pageYOffset || doc.scrollTop) - (doc.clientTop || 0)\n"\
"		];\n"\
"	},\n"\
"	getViewSize : function () {\n"\
"		var doc = window.document.documentElement;\n"\
"		return [\n"\
"			(window.innerWidth || doc.clientWidth),\n"\
"			(window.innerHeight || doc.clientHeight),\n"\
"		];\n"\
"	},\n"\
"	// r: 0-255\n"\
"	// g: 0-255\n"\
"	// b: 0-255\n"\
"	//\n"\
"	// returns: [ 0-360, 0-100, 0-100 ]\n"\
"	//\n"\
"	RGB_HSV : function (r, g, b) {\n"\
"		r /= 255;\n"\
"		g /= 255;\n"\
"		b /= 255;\n"\
"		var n = Math.min(Math.min(r,g),b);\n"\
"		var v = Math.max(Math.max(r,g),b);\n"\
"		var m = v - n;\n"\
"		if (m === 0) { return [ null, 0, 100 * v ]; }\n"\
"		var h = r===n ? 3+(b-g)/m : (g===n ? 5+(r-b)/m : 1+(g-r)/m);\n"\
"		return [\n"\
"			60 * (h===6?0:h),\n"\
"			100 * (m/v),\n"\
"			100 * v\n"\
"		];\n"\
"	},\n"\
"	// h: 0-360\n"\
"	// s: 0-100\n"\
"	// v: 0-100\n"\
"	//\n"\
"	// returns: [ 0-255, 0-255, 0-255 ]\n"\
"	//\n"\
"	HSV_RGB : function (h, s, v) {\n"\
"		var u = 255 * (v / 100);\n"\
"		if (h === null) {\n"\
"			return [ u, u, u ];\n"\
"		}\n"\
"		h /= 60;\n"\
"		s /= 100;\n"\
"		var i = Math.floor(h);\n"\
"		var f = i%2 ? h-i : 1-(h-i);\n"\
"		var m = u * (1 - s);\n"\
"		var n = u * (1 - s * f);\n"\
"		switch (i) {\n"\
"			case 6:\n"\
"			case 0: return [u,n,m];\n"\
"			case 1: return [n,u,m];\n"\
"			case 2: return [m,u,n];\n"\
"			case 3: return [m,n,u];\n"\
"			case 4: return [n,m,u];\n"\
"			case 5: return [u,m,n];\n"\
"		}\n"\
"	},\n"\
"	parseColorString : function (str) {\n"\
"		var ret = {\n"\
"			rgba: null,\n"\
"			format: null // 'hex' | 'hexa' | 'rgb' | 'rgba'\n"\
"		};\n"\
"		var m;\n"\
"		if (m = str.match(/^\\W*([0-9A-F]{3,8})\\W*$/i)) {\n"\
"			// HEX notation\n"\
"			if (m[1].length === 8) {\n"\
"				// 8-char notation (= with alpha)\n"\
"				ret.format = 'hexa';\n"\
"				ret.rgba = [\n"\
"					parseInt(m[1].slice(0,2),16),\n"\
"					parseInt(m[1].slice(2,4),16),\n"\
"					parseInt(m[1].slice(4,6),16),\n"\
"					parseInt(m[1].slice(6,8),16) / 255\n"\
"				];\n"\
"			} else if (m[1].length === 6) {\n"\
"				// 6-char notation\n"\
"				ret.format = 'hex';\n"\
"				ret.rgba = [\n"\
"					parseInt(m[1].slice(0,2),16),\n"\
"					parseInt(m[1].slice(2,4),16),\n"\
"					parseInt(m[1].slice(4,6),16),\n"\
"					null\n"\
"				];\n"\
"			} else if (m[1].length === 3) {\n"\
"				// 3-char notation\n"\
"				ret.format = 'hex';\n"\
"				ret.rgba = [\n"\
"					parseInt(m[1].charAt(0) + m[1].charAt(0),16),\n"\
"					parseInt(m[1].charAt(1) + m[1].charAt(1),16),\n"\
"					parseInt(m[1].charAt(2) + m[1].charAt(2),16),\n"\
"					null\n"\
"				];\n"\
"			} else {\n"\
"				return false;\n"\
"			}\n"\
"			return ret;\n"\
"		}\n"\
"		if (m = str.match(/^\\W*rgba?\(([^)]*)\)\\W*$/i)) {\n"\
"			// rgb(...) or rgba(...) notation\n"\
"			var par = m[1].split(',');\n"\
"			var re = /^\\s*(\d+|\d*\.\d+|\d+\.\d*)\\s*$/;\n"\
"			var mR, mG, mB, mA;\n"\
"			if (\n"\
"				par.length >= 3 &&\n"\
"				(mR = par[0].match(re)) &&\n"\
"				(mG = par[1].match(re)) &&\n"\
"				(mB = par[2].match(re))\n"\
"			) {\n"\
"				ret.format = 'rgb';\n"\
"				ret.rgba = [\n"\
"					parseFloat(mR[1]) || 0,\n"\
"					parseFloat(mG[1]) || 0,\n"\
"					parseFloat(mB[1]) || 0,\n"\
"					null\n"\
"				];\n"\
"				if (\n"\
"					par.length >= 4 &&\n"\
"					(mA = par[3].match(re))\n"\
"				) {\n"\
"					ret.format = 'rgba';\n"\
"					ret.rgba[3] = parseFloat(mA[1]) || 0;\n"\
"				}\n"\
"				return ret;\n"\
"			}\n"\
"		}\n"\
"		return false;\n"\
"	},\n"\
"	parsePaletteValue : function (mixed) {\n"\
"		var vals = [];\n"\
"		if (typeof mixed === 'string') { // input is a string of space separated color values\n"\
"			// rgb() and rgba() may contain spaces too, so let's find all color values by regex\n"\
"			mixed.replace(/#[0-9A-F]{3}([0-9A-F]{3})?|rgba?\(([^)]*)\)/ig, function (val) {\n"\
"				vals.push(val);\n"\
"			});\n"\
"		} else if (Array.isArray(mixed)) { // input is an array of color values\n"\
"			vals = mixed;\n"\
"		}\n"\
"		// convert all values into uniform color format\n"\
"		var colors = [];\n"\
"		for (var i = 0; i < vals.length; i++) {\n"\
"			var color = jsc.parseColorString(vals[i]);\n"\
"			if (color) {\n"\
"				colors.push(color);\n"\
"			}\n"\
"		}\n"\
"		return colors;\n"\
"	},\n"\
"	containsTranparentColor : function (colors) {\n"\
"		for (var i = 0; i < colors.length; i++) {\n"\
"			var a = colors[i].rgba[3];\n"\
"			if (a !== null && a < 1.0) {\n"\
"				return true;\n"\
"			}\n"\
"		}\n"\
"		return false;\n"\
"	},\n"\
"	isAlphaFormat : function (format) {\n"\
"		switch (format.toLowerCase()) {\n"\
"		case 'hexa':\n"\
"		case 'rgba':\n"\
"			return true;\n"\
"		}\n"\
"		return false;\n"\
"	},\n"\
"	// Canvas scaling for retina displays\n"\
"	//\n"\
"	// adapted from https://www.html5rocks.com/en/tutorials/canvas/hidpi/\n"\
"	//\n"\
"	scaleCanvasForHighDPR : function (canvas) {\n"\
"		var dpr = window.devicePixelRatio || 1;\n"\
"		canvas.width *= dpr;\n"\
"		canvas.height *= dpr;\n"\
"		var ctx = canvas.getContext('2d');\n"\
"		ctx.scale(dpr, dpr);\n"\
"	},\n"\
"	genColorPreviewCanvas : function (color, separatorPos, specWidth, scaleForHighDPR) {\n"\
"		var sepW = Math.round(jsc.pub.previewSeparator.length);\n"\
"		var sqSize = jsc.pub.chessboardSize;\n"\
"		var sqColor1 = jsc.pub.chessboardColor1;\n"\
"		var sqColor2 = jsc.pub.chessboardColor2;\n"\
"		var cWidth = specWidth ? specWidth : sqSize * 2;\n"\
"		var cHeight = sqSize * 2;\n"\
"		var canvas = jsc.createEl('canvas');\n"\
"		var ctx = canvas.getContext('2d');\n"\
"		canvas.width = cWidth;\n"\
"		canvas.height = cHeight;\n"\
"		if (scaleForHighDPR) {\n"\
"			jsc.scaleCanvasForHighDPR(canvas);\n"\
"		}\n"\
"		// transparency chessboard - background\n"\
"		ctx.fillStyle = sqColor1;\n"\
"		ctx.fillRect(0, 0, cWidth, cHeight);\n"\
"		// transparency chessboard - squares\n"\
"		ctx.fillStyle = sqColor2;\n"\
"		for (var x = 0; x < cWidth; x += sqSize * 2) {\n"\
"			ctx.fillRect(x, 0, sqSize, sqSize);\n"\
"			ctx.fillRect(x + sqSize, sqSize, sqSize, sqSize);\n"\
"		}\n"\
"		if (color) {\n"\
"			// actual color in foreground\n"\
"			ctx.fillStyle = color;\n"\
"			ctx.fillRect(0, 0, cWidth, cHeight);\n"\
"		}\n"\
"		var start = null;\n"\
"		switch (separatorPos) {\n"\
"			case 'left':\n"\
"				start = 0;\n"\
"				ctx.clearRect(0, 0, sepW/2, cHeight);\n"\
"				break;\n"\
"			case 'right':\n"\
"				start = cWidth - sepW;\n"\
"				ctx.clearRect(cWidth - (sepW/2), 0, sepW/2, cHeight);\n"\
"				break;\n"\
"		}\n"\
"		if (start !== null) {\n"\
"			ctx.lineWidth = 1;\n"\
"			for (var i = 0; i < jsc.pub.previewSeparator.length; i += 1) {\n"\
"				ctx.beginPath();\n"\
"				ctx.strokeStyle = jsc.pub.previewSeparator[i];\n"\
"				ctx.moveTo(0.5 + start + i, 0);\n"\
"				ctx.lineTo(0.5 + start + i, cHeight);\n"\
"				ctx.stroke();\n"\
"			}\n"\
"		}\n"\
"		return {\n"\
"			canvas: canvas,\n"\
"			width: cWidth,\n"\
"			height: cHeight,\n"\
"		};\n"\
"	},\n"\
"	// if position or width is not set => fill the entire element (0%-100%)\n"\
"	genColorPreviewGradient : function (color, position, width) {\n"\
"		var params = [];\n"\
"		if (position && width) {\n"\
"			params = [\n"\
"				'to ' + {'left':'right', 'right':'left'}[position],\n"\
"				color + ' 0%',\n"\
"				color + ' ' + width + 'px',\n"\
"				'rgba(0,0,0,0) ' + (width + 1) + 'px',\n"\
"				'rgba(0,0,0,0) 100%',\n"\
"			];\n"\
"		} else {\n"\
"			params = [\n"\
"				'to right',\n"\
"				color + ' 0%',\n"\
"				color + ' 100%',\n"\
"			];\n"\
"		}\n"\
"		return jsc.linearGradient.apply(this, params);\n"\
"	},\n"\
"	redrawPosition : function () {\n"\
"		if (!jsc.picker || !jsc.picker.owner) {\n"\
"			return; // picker is not shown\n"\
"		}\n"\
"		var thisObj = jsc.picker.owner;\n"\
"		var tp, vp;\n"\
"		if (thisObj.fixed) {\n"\
"			// Fixed elements are positioned relative to viewport,\n"\
"			// therefore we can ignore the scroll offset\n"\
"			tp = jsc.getElementPos(thisObj.targetElement, true); // target pos\n"\
"			vp = [0, 0]; // view pos\n"\
"		} else {\n"\
"			tp = jsc.getElementPos(thisObj.targetElement); // target pos\n"\
"			vp = jsc.getViewPos(); // view pos\n"\
"		}\n"\
"		var ts = jsc.getElementSize(thisObj.targetElement); // target size\n"\
"		var vs = jsc.getViewSize(); // view size\n"\
"		var pd = jsc.getPickerDims(thisObj);\n"\
"		var ps = [pd.borderW, pd.borderH]; // picker outer size\n"\
"		var a, b, c;\n"\
"		switch (thisObj.position.toLowerCase()) {\n"\
"			case 'left': a=1; b=0; c=-1; break;\n"\
"			case 'right':a=1; b=0; c=1; break;\n"\
"			case 'top':  a=0; b=1; c=-1; break;\n"\
"			default:     a=0; b=1; c=1; break;\n"\
"		}\n"\
"		var l = (ts[b]+ps[b])/2;\n"\
"		// compute picker position\n"\
"		if (!thisObj.smartPosition) {\n"\
"			var pp = [\n"\
"				tp[a],\n"\
"				tp[b]+ts[b]-l+l*c\n"\
"			];\n"\
"		} else {\n"\
"			var pp = [\n"\
"				-vp[a]+tp[a]+ps[a] > vs[a] ?\n"\
"					(-vp[a]+tp[a]+ts[a]/2 > vs[a]/2 && tp[a]+ts[a]-ps[a] >= 0 ? tp[a]+ts[a]-ps[a] : tp[a]) :\n"\
"					tp[a],\n"\
"				-vp[b]+tp[b]+ts[b]+ps[b]-l+l*c > vs[b] ?\n"\
"					(-vp[b]+tp[b]+ts[b]/2 > vs[b]/2 && tp[b]+ts[b]-l-l*c >= 0 ? tp[b]+ts[b]-l-l*c : tp[b]+ts[b]-l+l*c) :\n"\
"					(tp[b]+ts[b]-l+l*c >= 0 ? tp[b]+ts[b]-l+l*c : tp[b]+ts[b]-l-l*c)\n"\
"			];\n"\
"		}\n"\
"		var x = pp[a];\n"\
"		var y = pp[b];\n"\
"		var positionValue = thisObj.fixed ? 'fixed' : 'absolute';\n"\
"		var contractShadow =\n"\
"			(pp[0] + ps[0] > tp[0] || pp[0] < tp[0] + ts[0]) &&\n"\
"			(pp[1] + ps[1] < tp[1] + ts[1]);\n"\
"		jsc._drawPosition(thisObj, x, y, positionValue, contractShadow);\n"\
"	},\n"\
"	_drawPosition : function (thisObj, x, y, positionValue, contractShadow) {\n"\
"		var vShadow = contractShadow ? 0 : thisObj.shadowBlur; // px\n"\
"		jsc.picker.wrap.style.position = positionValue;\n"\
"		jsc.picker.wrap.style.left = x + 'px';\n"\
"		jsc.picker.wrap.style.top = y + 'px';\n"\
"		jsc.setBoxShadow(\n"\
"			jsc.picker.boxS,\n"\
"			thisObj.shadow ?\n"\
"				new jsc.BoxShadow(0, vShadow, thisObj.shadowBlur, 0, thisObj.shadowColor) :\n"\
"				null);\n"\
"	},\n"\
"	getPickerDims : function (thisObj) {\n"\
"		var w = 2 * thisObj.controlBorderWidth + thisObj.width;\n"\
"		var h = 2 * thisObj.controlBorderWidth + thisObj.height;\n"\
"		var sliderSpace = 2 * thisObj.controlBorderWidth + 2 * jsc.getControlPadding(thisObj) + thisObj.sliderSize;\n"\
"		if (jsc.getSliderChannel(thisObj)) {\n"\
"			w += sliderSpace;\n"\
"		}\n"\
"		if (thisObj.hasAlphaChannel()) {\n"\
"			w += sliderSpace;\n"\
"		}\n"\
"		var pal = jsc.getPaletteDims(thisObj, w);\n"\
"		if (pal.height) {\n"\
"			h += pal.height + thisObj.padding;\n"\
"		}\n"\
"		if (thisObj.closeButton) {\n"\
"			h += 2 * thisObj.controlBorderWidth + thisObj.padding + thisObj.buttonHeight;\n"\
"		}\n"\
"		var pW = w + (2 * thisObj.padding);\n"\
"		var pH = h + (2 * thisObj.padding);\n"\
"		return {\n"\
"			contentW: w,\n"\
"			contentH: h,\n"\
"			paddedW: pW,\n"\
"			paddedH: pH,\n"\
"			borderW: pW + (2 * thisObj.borderWidth),\n"\
"			borderH: pH + (2 * thisObj.borderWidth),\n"\
"			palette: pal,\n"\
"		};\n"\
"	},\n"\
"	getPaletteDims : function (thisObj, width) {\n"\
"		var cols = 0, rows = 0, cellW = 0, cellH = 0, height = 0;\n"\
"		var sampleCount = thisObj._palette ? thisObj._palette.length : 0;\n"\
"		if (sampleCount) {\n"\
"			cols = thisObj.paletteCols;\n"\
"			rows = cols > 0 ? Math.ceil(sampleCount / cols) : 0;\n"\
"			// color sample's dimensions (includes border)\n"\
"			cellW = Math.max(1, Math.floor((width - ((cols - 1) * thisObj.paletteSpacing)) / cols));\n"\
"			cellH = thisObj.paletteHeight ? Math.min(thisObj.paletteHeight, cellW) : cellW;\n"\
"		}\n"\
"		if (rows) {\n"\
"			height =\n"\
"				rows * cellH +\n"\
"				(rows - 1) * thisObj.paletteSpacing;\n"\
"		}\n"\
"		return {\n"\
"			cols: cols,\n"\
"			rows: rows,\n"\
"			cellW: cellW,\n"\
"			cellH: cellH,\n"\
"			width: width,\n"\
"			height: height,\n"\
"		};\n"\
"	},\n"\
"	getControlPadding : function (thisObj) {\n"\
"		return Math.max(\n"\
"			thisObj.padding / 2,\n"\
"			(2 * thisObj.pointerBorderWidth + thisObj.pointerThickness) - thisObj.controlBorderWidth\n"\
"		);\n"\
"	},\n"\
"	getPadYChannel : function (thisObj) {\n"\
"		switch (thisObj.mode.charAt(1).toLowerCase()) {\n"\
"			case 'v': return 'v'; break;\n"\
"		}\n"\
"		return 's';\n"\
"	},\n"\
"	getSliderChannel : function (thisObj) {\n"\
"		if (thisObj.mode.length > 2) {\n"\
"			switch (thisObj.mode.charAt(2).toLowerCase()) {\n"\
"				case 's': return 's'; break;\n"\
"				case 'v': return 'v'; break;\n"\
"			}\n"\
"		}\n"\
"		return null;\n"\
"	},\n"\
"	// calls function specified in picker's property\n"\
"	triggerCallback : function (thisObj, prop) {\n"\
"		if (!thisObj[prop]) {\n"\
"			return; // callback func not specified\n"\
"		}\n"\
"		var callback = null;\n"\
"		if (typeof thisObj[prop] === 'string') {\n"\
"			// string with code\n"\
"			try {\n"\
"				callback = new Function (thisObj[prop]);\n"\
"			} catch (e) {\n"\
"				console.error(e);\n"\
"			}\n"\
"		} else {\n"\
"			// function\n"\
"			callback = thisObj[prop];\n"\
"		}\n"\
"		if (callback) {\n"\
"			callback.call(thisObj);\n"\
"		}\n"\
"	},\n"\
"	// Triggers a color change related event(s) on all picker instances.\n"\
"	// It is possible to specify multiple events separated with a space.\n"\
"	triggerGlobal : function (eventNames) {\n"\
"		var inst = jsc.getInstances();\n"\
"		for (var i = 0; i < inst.length; i += 1) {\n"\
"			inst[i].trigger(eventNames);\n"\
"		}\n"\
"	},\n"\
"	_pointerMoveEvent : {\n"\
"		mouse: 'mousemove',\n"\
"		touch: 'touchmove'\n"\
"	},\n"\
"	_pointerEndEvent : {\n"\
"		mouse: 'mouseup',\n"\
"		touch: 'touchend'\n"\
"	},\n"\
"	_pointerOrigin : null,\n"\
"	onDocumentKeyUp : function (e) {\n"\
"		if (['Tab', 'Escape'].indexOf(jsc.eventKey(e)) !== -1) {\n"\
"			if (jsc.picker && jsc.picker.owner) {\n"\
"				jsc.picker.owner.tryHide();\n"\
"			}\n"\
"		}\n"\
"	},\n"\
"	onWindowResize : function (e) {\n"\
"		jsc.redrawPosition();\n"\
"	},\n"\
"	onWindowScroll : function (e) {\n"\
"		jsc.redrawPosition();\n"\
"	},\n"\
"	onParentScroll : function (e) {\n"\
"		// hide the picker when one of the parent elements is scrolled\n"\
"		if (jsc.picker && jsc.picker.owner) {\n"\
"			jsc.picker.owner.tryHide();\n"\
"		}\n"\
"	},\n"\
"	onDocumentMouseDown : function (e) {\n"\
"		var target = e.target || e.srcElement;\n"\
"		if (target.jscolor && target.jscolor instanceof jsc.pub) { // clicked targetElement -> show picker\n"\
"			if (target.jscolor.showOnClick && !target.disabled) {\n"\
"				target.jscolor.show();\n"\
"			}\n"\
"		} else if (jsc.getData(target, 'gui')) { // clicked jscolor's GUI element\n"\
"			var control = jsc.getData(target, 'control');\n"\
"			if (control) {\n"\
"				// jscolor's control\n"\
"				jsc.onControlPointerStart(e, target, jsc.getData(target, 'control'), 'mouse');\n"\
"			}\n"\
"		} else {\n"\
"			// mouse is outside the picker's controls -> hide the color picker!\n"\
"			if (jsc.picker && jsc.picker.owner) {\n"\
"				jsc.picker.owner.tryHide();\n"\
"			}\n"\
"		}\n"\
"	},\n"\
"	onPickerTouchStart : function (e) {\n"\
"		var target = e.target || e.srcElement;\n"\
"		if (jsc.getData(target, 'control')) {\n"\
"			jsc.onControlPointerStart(e, target, jsc.getData(target, 'control'), 'touch');\n"\
"		}\n"\
"	},\n"\
"	onControlPointerStart : function (e, target, controlName, pointerType) {\n"\
"		var thisObj = jsc.getData(target, 'instance');\n"\
"		jsc.preventDefault(e);\n"\
"		var registerDragEvents = function (doc, offset) {\n"\
"			jsc.attachGroupEvent('drag', doc, jsc._pointerMoveEvent[pointerType],\n"\
"				jsc.onDocumentPointerMove(e, target, controlName, pointerType, offset));\n"\
"			jsc.attachGroupEvent('drag', doc, jsc._pointerEndEvent[pointerType],\n"\
"				jsc.onDocumentPointerEnd(e, target, controlName, pointerType));\n"\
"		};\n"\
"		registerDragEvents(window.document, [0, 0]);\n"\
"		if (window.parent && window.frameElement) {\n"\
"			var rect = window.frameElement.getBoundingClientRect();\n"\
"			var ofs = [-rect.left, -rect.top];\n"\
"			registerDragEvents(window.parent.window.document, ofs);\n"\
"		}\n"\
"		var abs = jsc.getAbsPointerPos(e);\n"\
"		var rel = jsc.getRelPointerPos(e);\n"\
"		jsc._pointerOrigin = {\n"\
"			x: abs.x - rel.x,\n"\
"			y: abs.y - rel.y\n"\
"		};\n"\
"		switch (controlName) {\n"\
"		case 'pad':\n"\
"			// if the value slider is at the bottom, move it up\n"\
"			if (jsc.getSliderChannel(thisObj) === 'v' && thisObj.channels.v === 0) {\n"\
"				thisObj.fromHSVA(null, null, 100, null);\n"\
"			}\n"\
"			jsc.setPad(thisObj, e, 0, 0);\n"\
"			break;\n"\
"		case 'sld':\n"\
"			jsc.setSld(thisObj, e, 0);\n"\
"			break;\n"\
"		case 'asld':\n"\
"			jsc.setASld(thisObj, e, 0);\n"\
"			break;\n"\
"		}\n"\
"		thisObj.trigger('input');\n"\
"	},\n"\
"	onDocumentPointerMove : function (e, target, controlName, pointerType, offset) {\n"\
"		return function (e) {\n"\
"			var thisObj = jsc.getData(target, 'instance');\n"\
"			switch (controlName) {\n"\
"			case 'pad':\n"\
"				jsc.setPad(thisObj, e, offset[0], offset[1]);\n"\
"				break;\n"\
"			case 'sld':\n"\
"				jsc.setSld(thisObj, e, offset[1]);\n"\
"				break;\n"\
"			case 'asld':\n"\
"				jsc.setASld(thisObj, e, offset[1]);\n"\
"				break;\n"\
"			}\n"\
"			thisObj.trigger('input');\n"\
"		}\n"\
"	},\n"\
"	onDocumentPointerEnd : function (e, target, controlName, pointerType) {\n"\
"		return function (e) {\n"\
"			var thisObj = jsc.getData(target, 'instance');\n"\
"			jsc.detachGroupEvents('drag');\n"\
"			// Always trigger changes AFTER detaching outstanding mouse handlers,\n"\
"			// in case some color change that occured in user-defined onChange/onInput handler\n"\
"			// intruded into current mouse events\n"\
"			thisObj.trigger('input');\n"\
"			thisObj.trigger('change');\n"\
"		};\n"\
"	},\n"\
"	onPaletteSampleClick : function (e) {\n"\
"		var target = e.currentTarget;\n"\
"		var thisObj = jsc.getData(target, 'instance');\n"\
"		var color = jsc.getData(target, 'color');\n"\
"		// when format is flexible, use the original format of this color sample\n"\
"		if (thisObj.format.toLowerCase() === 'any') {\n"\
"			thisObj._setFormat(color.format); // adapt format\n"\
"			if (!jsc.isAlphaFormat(thisObj.getFormat())) {\n"\
"				color.rgba[3] = 1.0; // when switching to a format that doesn't support alpha, set full opacity\n"\
"			}\n"\
"		}\n"\
"		// if this color doesn't specify alpha, use alpha of 1.0 (if applicable)\n"\
"		if (color.rgba[3] === null) {\n"\
"			if (thisObj.paletteSetsAlpha === true || (thisObj.paletteSetsAlpha === 'auto' && thisObj._paletteHasTransparency)) {\n"\
"				color.rgba[3] = 1.0;\n"\
"			}\n"\
"		}\n"\
"		thisObj.fromRGBA.apply(thisObj, color.rgba);\n"\
"		thisObj.trigger('input');\n"\
"		thisObj.trigger('change');\n"\
"		if (thisObj.hideOnPaletteClick) {\n"\
"			thisObj.hide();\n"\
"		}\n"\
"	},\n"\
"	setPad : function (thisObj, e, ofsX, ofsY) {\n"\
"		var pointerAbs = jsc.getAbsPointerPos(e);\n"\
"		var x = ofsX + pointerAbs.x - jsc._pointerOrigin.x - thisObj.padding - thisObj.controlBorderWidth;\n"\
"		var y = ofsY + pointerAbs.y - jsc._pointerOrigin.y - thisObj.padding - thisObj.controlBorderWidth;\n"\
"		var xVal = x * (360 / (thisObj.width - 1));\n"\
"		var yVal = 100 - (y * (100 / (thisObj.height - 1)));\n"\
"		switch (jsc.getPadYChannel(thisObj)) {\n"\
"		case 's': thisObj.fromHSVA(xVal, yVal, null, null); break;\n"\
"		case 'v': thisObj.fromHSVA(xVal, null, yVal, null); break;\n"\
"		}\n"\
"	},\n"\
"	setSld : function (thisObj, e, ofsY) {\n"\
"		var pointerAbs = jsc.getAbsPointerPos(e);\n"\
"		var y = ofsY + pointerAbs.y - jsc._pointerOrigin.y - thisObj.padding - thisObj.controlBorderWidth;\n"\
"		var yVal = 100 - (y * (100 / (thisObj.height - 1)));\n"\
"		switch (jsc.getSliderChannel(thisObj)) {\n"\
"		case 's': thisObj.fromHSVA(null, yVal, null, null); break;\n"\
"		case 'v': thisObj.fromHSVA(null, null, yVal, null); break;\n"\
"		}\n"\
"	},\n"\
"	setASld : function (thisObj, e, ofsY) {\n"\
"		var pointerAbs = jsc.getAbsPointerPos(e);\n"\
"		var y = ofsY + pointerAbs.y - jsc._pointerOrigin.y - thisObj.padding - thisObj.controlBorderWidth;\n"\
"		var yVal = 1.0 - (y * (1.0 / (thisObj.height - 1)));\n"\
"		if (yVal < 1.0) {\n"\
"			// if format is flexible and the current format doesn't support alpha, switch to a suitable one\n"\
"			var fmt = thisObj.getFormat();\n"\
"			if (thisObj.format.toLowerCase() === 'any' && !jsc.isAlphaFormat(fmt)) {\n"\
"				thisObj._setFormat(fmt === 'hex' ? 'hexa' : 'rgba');\n"\
"			}\n"\
"		}\n"\
"		thisObj.fromHSVA(null, null, null, yVal);\n"\
"	},\n"\
"	createPadCanvas : function () {\n"\
"		var ret = {\n"\
"			elm: null,\n"\
"			draw: null\n"\
"		};\n"\
"		var canvas = jsc.createEl('canvas');\n"\
"		var ctx = canvas.getContext('2d');\n"\
"		var drawFunc = function (width, height, type) {\n"\
"			canvas.width = width;\n"\
"			canvas.height = height;\n"\
"			ctx.clearRect(0, 0, canvas.width, canvas.height);\n"\
"			var hGrad = ctx.createLinearGradient(0, 0, canvas.width, 0);\n"\
"			hGrad.addColorStop(0 / 6, '#F00');\n"\
"			hGrad.addColorStop(1 / 6, '#FF0');\n"\
"			hGrad.addColorStop(2 / 6, '#0F0');\n"\
"			hGrad.addColorStop(3 / 6, '#0FF');\n"\
"			hGrad.addColorStop(4 / 6, '#00F');\n"\
"			hGrad.addColorStop(5 / 6, '#F0F');\n"\
"			hGrad.addColorStop(6 / 6, '#F00');\n"\
"			ctx.fillStyle = hGrad;\n"\
"			ctx.fillRect(0, 0, canvas.width, canvas.height);\n"\
"			var vGrad = ctx.createLinearGradient(0, 0, 0, canvas.height);\n"\
"			switch (type.toLowerCase()) {\n"\
"			case 's':\n"\
"				vGrad.addColorStop(0, 'rgba(255,255,255,0)');\n"\
"				vGrad.addColorStop(1, 'rgba(255,255,255,1)');\n"\
"				break;\n"\
"			case 'v':\n"\
"				vGrad.addColorStop(0, 'rgba(0,0,0,0)');\n"\
"				vGrad.addColorStop(1, 'rgba(0,0,0,1)');\n"\
"				break;\n"\
"			}\n"\
"			ctx.fillStyle = vGrad;\n"\
"			ctx.fillRect(0, 0, canvas.width, canvas.height);\n"\
"		};\n"\
"		ret.elm = canvas;\n"\
"		ret.draw = drawFunc;\n"\
"		return ret;\n"\
"	},\n"\
"	createSliderGradient : function () {\n"\
"		var ret = {\n"\
"			elm: null,\n"\
"			draw: null\n"\
"		};\n"\
"		var canvas = jsc.createEl('canvas');\n"\
"		var ctx = canvas.getContext('2d');\n"\
"		var drawFunc = function (width, height, color1, color2) {\n"\
"			canvas.width = width;\n"\
"			canvas.height = height;\n"\
"			ctx.clearRect(0, 0, canvas.width, canvas.height);\n"\
"			var grad = ctx.createLinearGradient(0, 0, 0, canvas.height);\n"\
"			grad.addColorStop(0, color1);\n"\
"			grad.addColorStop(1, color2);\n"\
"			ctx.fillStyle = grad;\n"\
"			ctx.fillRect(0, 0, canvas.width, canvas.height);\n"\
"		};\n"\
"		ret.elm = canvas;\n"\
"		ret.draw = drawFunc;\n"\
"		return ret;\n"\
"	},\n"\
"	createASliderGradient : function () {\n"\
"		var ret = {\n"\
"			elm: null,\n"\
"			draw: null\n"\
"		};\n"\
"		var canvas = jsc.createEl('canvas');\n"\
"		var ctx = canvas.getContext('2d');\n"\
"		var drawFunc = function (width, height, color) {\n"\
"			canvas.width = width;\n"\
"			canvas.height = height;\n"\
"			ctx.clearRect(0, 0, canvas.width, canvas.height);\n"\
"			var sqSize = canvas.width / 2;\n"\
"			var sqColor1 = jsc.pub.chessboardColor1;\n"\
"			var sqColor2 = jsc.pub.chessboardColor2;\n"\
"			// dark gray background\n"\
"			ctx.fillStyle = sqColor1;\n"\
"			ctx.fillRect(0, 0, canvas.width, canvas.height);\n"\
"			if (sqSize > 0) { // to avoid infinite loop\n"\
"				for (var y = 0; y < canvas.height; y += sqSize * 2) {\n"\
"					// light gray squares\n"\
"					ctx.fillStyle = sqColor2;\n"\
"					ctx.fillRect(0, y, sqSize, sqSize);\n"\
"					ctx.fillRect(sqSize, y + sqSize, sqSize, sqSize);\n"\
"				}\n"\
"			}\n"\
"			var grad = ctx.createLinearGradient(0, 0, 0, canvas.height);\n"\
"			grad.addColorStop(0, color);\n"\
"			grad.addColorStop(1, 'rgba(0,0,0,0)');\n"\
"			ctx.fillStyle = grad;\n"\
"			ctx.fillRect(0, 0, canvas.width, canvas.height);\n"\
"		};\n"\
"		ret.elm = canvas;\n"\
"		ret.draw = drawFunc;\n"\
"		return ret;\n"\
"	},\n"\
"	BoxShadow : (function () {\n"\
"		var BoxShadow = function (hShadow, vShadow, blur, spread, color, inset) {\n"\
"			this.hShadow = hShadow;\n"\
"			this.vShadow = vShadow;\n"\
"			this.blur = blur;\n"\
"			this.spread = spread;\n"\
"			this.color = color;\n"\
"			this.inset = !!inset;\n"\
"		};\n"\
"		BoxShadow.prototype.toString = function () {\n"\
"			var vals = [\n"\
"				Math.round(this.hShadow) + 'px',\n"\
"				Math.round(this.vShadow) + 'px',\n"\
"				Math.round(this.blur) + 'px',\n"\
"				Math.round(this.spread) + 'px',\n"\
"				this.color\n"\
"			];\n"\
"			if (this.inset) {\n"\
"				vals.push('inset');\n"\
"			}\n"\
"			return vals.join(' ');\n"\
"		};\n"\
"		return BoxShadow;\n"\
"	})(),\n"\
"	flags : {\n"\
"		leaveValue : 1 << 0,\n"\
"		leaveAlpha : 1 << 1,\n"\
"		leavePreview : 1 << 2,\n"\
"	},\n"\
"	enumOpts : {\n"\
"		format: ['auto', 'any', 'hex', 'hexa', 'rgb', 'rgba'],\n"\
"		previewPosition: ['left', 'right'],\n"\
"		mode: ['hsv', 'hvs', 'hs', 'hv'],\n"\
"		position: ['left', 'right', 'top', 'bottom'],\n"\
"		alphaChannel: ['auto', true, false],\n"\
"		paletteSetsAlpha: ['auto', true, false],\n"\
"	},\n"\
"	deprecatedOpts : {\n"\
"		// <old_option>: <new_option>  (<new_option> can be null)\n"\
"		'styleElement': 'previewElement',\n"\
"		'onFineChange': 'onInput',\n"\
"		'overwriteImportant': 'forceStyle',\n"\
"		'closable': 'closeButton',\n"\
"		'insetWidth': 'controlBorderWidth',\n"\
"		'insetColor': 'controlBorderColor',\n"\
"		'refine': null,\n"\
"	},\n"\
"	docsRef : ' ' + 'See https://jscolor.com/docs/',\n"\
"	//\n"\
"	// Usage:\n"\
"	// var myPicker = new JSColor(<targetElement> [, <options>])\n"\
"	//\n"\
"	// (constructor is accessible via both 'jscolor' and 'JSColor' name)\n"\
"	//\n"\
"	pub : function (targetElement, opts) {\n"\
"		var THIS = this;\n"\
"		if (!opts) {\n"\
"			opts = {};\n"\
"		}\n"\
"		this.channels = {\n"\
"			r: 255, // red [0-255]\n"\
"			g: 255, // green [0-255]\n"\
"			b: 255, // blue [0-255]\n"\
"			h: 0, // hue [0-360]\n"\
"			s: 0, // saturation [0-100]\n"\
"			v: 100, // value (brightness) [0-100]\n"\
"			a: 1.0, // alpha (opacity) [0.0 - 1.0]\n"\
"		};\n"\
"		// General options\n"\
"		//\n"\
"		this.format = 'auto'; // 'auto' | 'any' | 'hex' | 'hexa' | 'rgb' | 'rgba' - Format of the input/output value\n"\
"		this.value = undefined; // INITIAL color value in any supported format. To change it later, use method fromString(), fromHSVA(), fromRGBA() or channel()\n"\
"		this.alpha = undefined; // INITIAL alpha value. To change it later, call method channel('A', <value>)\n"\
"		this.random = false; // whether to randomize the initial color. Either true | false, or an array of ranges: [minV, maxV, minS, maxS, minH, maxH, minA, maxA]\n"\
"		this.onChange = undefined; // called when color changes. Value can be either a function or a string with JS code.\n"\
"		this.onInput = undefined; // called repeatedly as the color is being changed, e.g. while dragging a slider. Value can be either a function or a string with JS code.\n"\
"		this.valueElement = undefined; // element that will be used to display and input the color value\n"\
"		this.alphaElement = undefined; // element that will be used to display and input the alpha (opacity) value\n"\
"		this.previewElement = undefined; // element that will preview the picked color using CSS background\n"\
"		this.previewPosition = 'left'; // 'left' | 'right' - position of the color preview in previewElement\n"\
"		this.previewSize = 32; // (px) width of the color preview displayed in previewElement\n"\
"		this.previewPadding = 8; // (px) space between color preview and content of the previewElement\n"\
"		this.required = true; // whether the associated text input must always contain a color value. If false, the input can be left empty.\n"\
"		this.hash = true; // whether to prefix the HEX color code with # symbol (only applicable for HEX format)\n"\
"		this.uppercase = true; // whether to show the HEX color code in upper case (only applicable for HEX format)\n"\
"		this.forceStyle = true; // whether to overwrite CSS style of the previewElement using !important flag\n"\
"		// Color Picker options\n"\
"		//\n"\
"		this.width = 181; // width of the color spectrum (in px)\n"\
"		this.height = 101; // height of the color spectrum (in px)\n"\
"		this.mode = 'HSV'; // 'HSV' | 'HVS' | 'HS' | 'HV' - layout of the color picker controls\n"\
"		this.alphaChannel = 'auto'; // 'auto' | true | false - if alpha channel is enabled, the alpha slider will be visible. If 'auto', it will be determined according to color format\n"\
"		this.position = 'bottom'; // 'left' | 'right' | 'top' | 'bottom' - position relative to the target element\n"\
"		this.smartPosition = true; // automatically change picker position when there is not enough space for it\n"\
"		this.showOnClick = true; // whether to show the picker when user clicks its target element\n"\
"		this.hideOnLeave = true; // whether to automatically hide the picker when user leaves its target element (e.g. upon clicking the document)\n"\
"		this.palette = []; // colors to be displayed in the palette, specified as an array or a string of space separated color values (in any supported format)\n"\
"		this.paletteCols = 10; // number of columns in the palette\n"\
"		this.paletteSetsAlpha = 'auto'; // 'auto' | true | false - if true, palette colors that don't specify alpha will set alpha to 1.0\n"\
"		this.paletteHeight = 16; // maximum height (px) of a row in the palette\n"\
"		this.paletteSpacing = 4; // distance (px) between color samples in the palette\n"\
"		this.hideOnPaletteClick = false; // when set to true, clicking the palette will also hide the color picker\n"\
"		this.sliderSize = 16; // px\n"\
"		this.crossSize = 8; // px\n"\
"		this.closeButton = false; // whether to display the Close button\n"\
"		this.closeText = 'Close';\n"\
"		this.buttonColor = 'rgba(0,0,0,1)'; // CSS color\n"\
"		this.buttonHeight = 18; // px\n"\
"		this.padding = 12; // px\n"\
"		this.backgroundColor = 'rgba(255,255,255,1)'; // CSS color\n"\
"		this.borderWidth = 1; // px\n"\
"		this.borderColor = 'rgba(187,187,187,1)'; // CSS color\n"\
"		this.borderRadius = 8; // px\n"\
"		this.controlBorderWidth = 1; // px\n"\
"		this.controlBorderColor = 'rgba(187,187,187,1)'; // CSS color\n"\
"		this.shadow = true; // whether to display a shadow\n"\
"		this.shadowBlur = 15; // px\n"\
"		this.shadowColor = 'rgba(0,0,0,0.2)'; // CSS color\n"\
"		this.pointerColor = 'rgba(76,76,76,1)'; // CSS color\n"\
"		this.pointerBorderWidth = 1; // px\n"\
"		this.pointerBorderColor = 'rgba(255,255,255,1)'; // CSS color\n"\
"		this.pointerThickness = 2; // px\n"\
"		this.zIndex = 5000;\n"\
"		this.container = undefined; // where to append the color picker (BODY element by default)\n"\
"		// Experimental\n"\
"		//\n"\
"		this.minS = 0; // min allowed saturation (0 - 100)\n"\
"		this.maxS = 100; // max allowed saturation (0 - 100)\n"\
"		this.minV = 0; // min allowed value (brightness) (0 - 100)\n"\
"		this.maxV = 100; // max allowed value (brightness) (0 - 100)\n"\
"		this.minA = 0.0; // min allowed alpha (opacity) (0.0 - 1.0)\n"\
"		this.maxA = 1.0; // max allowed alpha (opacity) (0.0 - 1.0)\n"\
"		// Getter: option(name)\n"\
"		// Setter: option(name, value)\n"\
"		//         option({name:value, ...})\n"\
"		//\n"\
"		this.option = function () {\n"\
"			if (!arguments.length) {\n"\
"				throw new Error('No option specified');\n"\
"			}\n"\
"			if (arguments.length === 1 && typeof arguments[0] === 'string') {\n"\
"				// getting a single option\n"\
"				try {\n"\
"					return getOption(arguments[0]);\n"\
"				} catch (e) {\n"\
"					console.warn(e);\n"\
"				}\n"\
"				return false;\n"\
"			} else if (arguments.length >= 2 && typeof arguments[0] === 'string') {\n"\
"				// setting a single option\n"\
"				try {\n"\
"					if (!setOption(arguments[0], arguments[1])) {\n"\
"						return false;\n"\
"					}\n"\
"				} catch (e) {\n"\
"					console.warn(e);\n"\
"					return false;\n"\
"				}\n"\
"				this.redraw(); // immediately redraws the picker, if it's displayed\n"\
"				this.exposeColor(); // in case some preview-related or format-related option was changed\n"\
"				return true;\n"\
"			} else if (arguments.length === 1 && typeof arguments[0] === 'object') {\n"\
"				// setting multiple options\n"\
"				var opts = arguments[0];\n"\
"				var success = true;\n"\
"				for (var opt in opts) {\n"\
"					if (opts.hasOwnProperty(opt)) {\n"\
"						try {\n"\
"							if (!setOption(opt, opts[opt])) {\n"\
"								success = false;\n"\
"							}\n"\
"						} catch (e) {\n"\
"							console.warn(e);\n"\
"							success = false;\n"\
"						}\n"\
"					}\n"\
"				}\n"\
"				this.redraw(); // immediately redraws the picker, if it's displayed\n"\
"				this.exposeColor(); // in case some preview-related or format-related option was changed\n"\
"				return success;\n"\
"			}\n"\
"			throw new Error('Invalid arguments');\n"\
"		}\n"\
"		// Getter: channel(name)\n"\
"		// Setter: channel(name, value)\n"\
"		//\n"\
"		this.channel = function (name, value) {\n"\
"			if (typeof name !== 'string') {\n"\
"				throw new Error('Invalid value for channel name: ' + name);\n"\
"			}\n"\
"			if (value === undefined) {\n"\
"				// getting channel value\n"\
"				if (!this.channels.hasOwnProperty(name.toLowerCase())) {\n"\
"					console.warn('Getting unknown channel: ' + name);\n"\
"					return false;\n"\
"				}\n"\
"				return this.channels[name.toLowerCase()];\n"\
"			} else {\n"\
"				// setting channel value\n"\
"				var res = false;\n"\
"				switch (name.toLowerCase()) {\n"\
"					case 'r': res = this.fromRGBA(value, null, null, null); break;\n"\
"					case 'g': res = this.fromRGBA(null, value, null, null); break;\n"\
"					case 'b': res = this.fromRGBA(null, null, value, null); break;\n"\
"					case 'h': res = this.fromHSVA(value, null, null, null); break;\n"\
"					case 's': res = this.fromHSVA(null, value, null, null); break;\n"\
"					case 'v': res = this.fromHSVA(null, null, value, null); break;\n"\
"					case 'a': res = this.fromHSVA(null, null, null, value); break;\n"\
"					default:\n"\
"						console.warn('Setting unknown channel: ' + name);\n"\
"						return false;\n"\
"				}\n"\
"				if (res) {\n"\
"					this.redraw(); // immediately redraws the picker, if it's displayed\n"\
"					return true;\n"\
"				}\n"\
"			}\n"\
"			return false;\n"\
"		}\n"\
"		// Triggers given input event(s) by:\n"\
"		// - executing on<Event> callback specified as picker's option\n"\
"		// - triggering standard DOM event listeners attached to the value element\n"\
"		//\n"\
"		// It is possible to specify multiple events separated with a space.\n"\
"		//\n"\
"		this.trigger = function (eventNames) {\n"\
"			var evs = jsc.strList(eventNames);\n"\
"			for (var i = 0; i < evs.length; i += 1) {\n"\
"				var ev = evs[i].toLowerCase();\n"\
"				// trigger a callback\n"\
"				var callbackProp = null;\n"\
"				switch (ev) {\n"\
"					case 'input': callbackProp = 'onInput'; break;\n"\
"					case 'change': callbackProp = 'onChange'; break;\n"\
"				}\n"\
"				if (callbackProp) {\n"\
"					jsc.triggerCallback(this, callbackProp);\n"\
"				}\n"\
"				// trigger standard DOM event listeners on the value element\n"\
"				jsc.triggerInputEvent(this.valueElement, ev, true, true);\n"\
"			}\n"\
"		};\n"\
"		// h: 0-360\n"\
"		// s: 0-100\n"\
"		// v: 0-100\n"\
"		// a: 0.0-1.0\n"\
"		//\n"\
"		this.fromHSVA = function (h, s, v, a, flags) { // null = don't change\n"\
"			if (h === undefined) { h = null; }\n"\
"			if (s === undefined) { s = null; }\n"\
"			if (v === undefined) { v = null; }\n"\
"			if (a === undefined) { a = null; }\n"\
"			if (h !== null) {\n"\
"				if (isNaN(h)) { return false; }\n"\
"				this.channels.h = Math.max(0, Math.min(360, h));\n"\
"			}\n"\
"			if (s !== null) {\n"\
"				if (isNaN(s)) { return false; }\n"\
"				this.channels.s = Math.max(0, Math.min(100, this.maxS, s), this.minS);\n"\
"			}\n"\
"			if (v !== null) {\n"\
"				if (isNaN(v)) { return false; }\n"\
"				this.channels.v = Math.max(0, Math.min(100, this.maxV, v), this.minV);\n"\
"			}\n"\
"			if (a !== null) {\n"\
"				if (isNaN(a)) { return false; }\n"\
"				this.channels.a = this.hasAlphaChannel() ?\n"\
"					Math.max(0, Math.min(1, this.maxA, a), this.minA) :\n"\
"					1.0; // if alpha channel is disabled, the color should stay 100% opaque\n"\
"			}\n"\
"			var rgb = jsc.HSV_RGB(\n"\
"				this.channels.h,\n"\
"				this.channels.s,\n"\
"				this.channels.v\n"\
"			);\n"\
"			this.channels.r = rgb[0];\n"\
"			this.channels.g = rgb[1];\n"\
"			this.channels.b = rgb[2];\n"\
"			this.exposeColor(flags);\n"\
"			return true;\n"\
"		};\n"\
"		// r: 0-255\n"\
"		// g: 0-255\n"\
"		// b: 0-255\n"\
"		// a: 0.0-1.0\n"\
"		//\n"\
"		this.fromRGBA = function (r, g, b, a, flags) { // null = don't change\n"\
"			if (r === undefined) { r = null; }\n"\
"			if (g === undefined) { g = null; }\n"\
"			if (b === undefined) { b = null; }\n"\
"			if (a === undefined) { a = null; }\n"\
"			if (r !== null) {\n"\
"				if (isNaN(r)) { return false; }\n"\
"				r = Math.max(0, Math.min(255, r));\n"\
"			}\n"\
"			if (g !== null) {\n"\
"				if (isNaN(g)) { return false; }\n"\
"				g = Math.max(0, Math.min(255, g));\n"\
"			}\n"\
"			if (b !== null) {\n"\
"				if (isNaN(b)) { return false; }\n"\
"				b = Math.max(0, Math.min(255, b));\n"\
"			}\n"\
"			if (a !== null) {\n"\
"				if (isNaN(a)) { return false; }\n"\
"				this.channels.a = this.hasAlphaChannel() ?\n"\
"					Math.max(0, Math.min(1, this.maxA, a), this.minA) :\n"\
"					1.0; // if alpha channel is disabled, the color should stay 100% opaque\n"\
"			}\n"\
"			var hsv = jsc.RGB_HSV(\n"\
"				r===null ? this.channels.r : r,\n"\
"				g===null ? this.channels.g : g,\n"\
"				b===null ? this.channels.b : b\n"\
"			);\n"\
"			if (hsv[0] !== null) {\n"\
"				this.channels.h = Math.max(0, Math.min(360, hsv[0]));\n"\
"			}\n"\
"			if (hsv[2] !== 0) { // fully black color stays black through entire saturation range, so let's not change saturation\n"\
"				this.channels.s = Math.max(0, this.minS, Math.min(100, this.maxS, hsv[1]));\n"\
"			}\n"\
"			this.channels.v = Math.max(0, this.minV, Math.min(100, this.maxV, hsv[2]));\n"\
"			// update RGB according to final HSV, as some values might be trimmed\n"\
"			var rgb = jsc.HSV_RGB(this.channels.h, this.channels.s, this.channels.v);\n"\
"			this.channels.r = rgb[0];\n"\
"			this.channels.g = rgb[1];\n"\
"			this.channels.b = rgb[2];\n"\
"			this.exposeColor(flags);\n"\
"			return true;\n"\
"		};\n"\
"		// DEPRECATED. Use .fromHSVA() instead\n"\
"		//\n"\
"		this.fromHSV = function (h, s, v, flags) {\n"\
"			console.warn('fromHSV() method is DEPRECATED. Using fromHSVA() instead.' + jsc.docsRef);\n"\
"			return this.fromHSVA(h, s, v, null, flags);\n"\
"		};\n"\
"		// DEPRECATED. Use .fromRGBA() instead\n"\
"		//\n"\
"		this.fromRGB = function (r, g, b, flags) {\n"\
"			console.warn('fromRGB() method is DEPRECATED. Using fromRGBA() instead.' + jsc.docsRef);\n"\
"			return this.fromRGBA(r, g, b, null, flags);\n"\
"		};\n"\
"		this.fromString = function (str, flags) {\n"\
"			if (!this.required && str.trim() === '') {\n"\
"				// setting empty string to an optional color input\n"\
"				this.setPreviewElementBg(null);\n"\
"				this.setValueElementValue('');\n"\
"				return true;\n"\
"			}\n"\
"			var color = jsc.parseColorString(str);\n"\
"			if (!color) {\n"\
"				return false; // could not parse\n"\
"			}\n"\
"			if (this.format.toLowerCase() === 'any') {\n"\
"				this._setFormat(color.format); // adapt format\n"\
"				if (!jsc.isAlphaFormat(this.getFormat())) {\n"\
"					color.rgba[3] = 1.0; // when switching to a format that doesn't support alpha, set full opacity\n"\
"				}\n"\
"			}\n"\
"			this.fromRGBA(\n"\
"				color.rgba[0],\n"\
"				color.rgba[1],\n"\
"				color.rgba[2],\n"\
"				color.rgba[3],\n"\
"				flags\n"\
"			);\n"\
"			return true;\n"\
"		};\n"\
"		this.randomize = function (minV, maxV, minS, maxS, minH, maxH, minA, maxA) {\n"\
"			if (minV === undefined) { minV = 0; }\n"\
"			if (maxV === undefined) { maxV = 100; }\n"\
"			if (minS === undefined) { minS = 0; }\n"\
"			if (maxS === undefined) { maxS = 100; }\n"\
"			if (minH === undefined) { minH = 0; }\n"\
"			if (maxH === undefined) { maxH = 359; }\n"\
"			if (minA === undefined) { minA = 1; }\n"\
"			if (maxA === undefined) { maxA = 1; }\n"\
"			this.fromHSVA(\n"\
"				minH + Math.floor(Math.random() * (maxH - minH + 1)),\n"\
"				minS + Math.floor(Math.random() * (maxS - minS + 1)),\n"\
"				minV + Math.floor(Math.random() * (maxV - minV + 1)),\n"\
"				((100 * minA) + Math.floor(Math.random() * (100 * (maxA - minA) + 1))) / 100\n"\
"			);\n"\
"		};\n"\
"		this.toString = function (format) {\n"\
"			if (format === undefined) {\n"\
"				format = this.getFormat(); // format not specified -> use the current format\n"\
"			}\n"\
"			switch (format.toLowerCase()) {\n"\
"				case 'hex': return this.toHEXString(); break;\n"\
"				case 'hexa': return this.toHEXAString(); break;\n"\
"				case 'rgb': return this.toRGBString(); break;\n"\
"				case 'rgba': return this.toRGBAString(); break;\n"\
"			}\n"\
"			return false;\n"\
"		};\n"\
"		this.toHEXString = function () {\n"\
"			return jsc.hexColor(\n"\
"				this.channels.r,\n"\
"				this.channels.g,\n"\
"				this.channels.b\n"\
"			);\n"\
"		};\n"\
"		this.toHEXAString = function () {\n"\
"			return jsc.hexaColor(\n"\
"				this.channels.r,\n"\
"				this.channels.g,\n"\
"				this.channels.b,\n"\
"				this.channels.a\n"\
"			);\n"\
"		};\n"\
"		this.toRGBString = function () {\n"\
"			return jsc.rgbColor(\n"\
"				this.channels.r,\n"\
"				this.channels.g,\n"\
"				this.channels.b\n"\
"			);\n"\
"		};\n"\
"		this.toRGBAString = function () {\n"\
"			return jsc.rgbaColor(\n"\
"				this.channels.r,\n"\
"				this.channels.g,\n"\
"				this.channels.b,\n"\
"				this.channels.a\n"\
"			);\n"\
"		};\n"\
"		this.toGrayscale = function () {\n"\
"			return (\n"\
"				0.213 * this.channels.r +\n"\
"				0.715 * this.channels.g +\n"\
"				0.072 * this.channels.b\n"\
"			);\n"\
"		};\n"\
"		this.toCanvas = function () {\n"\
"			return jsc.genColorPreviewCanvas(this.toRGBAString()).canvas;\n"\
"		};\n"\
"		this.toDataURL = function () {\n"\
"			return this.toCanvas().toDataURL();\n"\
"		};\n"\
"		this.toBackground = function () {\n"\
"			return jsc.pub.background(this.toRGBAString());\n"\
"		};\n"\
"		this.isLight = function () {\n"\
"			return this.toGrayscale() > 255 / 2;\n"\
"		};\n"\
"		this.hide = function () {\n"\
"			if (isPickerOwner()) {\n"\
"				detachPicker();\n"\
"			}\n"\
"		};\n"\
"		this.show = function () {\n"\
"			drawPicker();\n"\
"		};\n"\
"		this.redraw = function () {\n"\
"			if (isPickerOwner()) {\n"\
"				drawPicker();\n"\
"			}\n"\
"		};\n"\
"		this.getFormat = function () {\n"\
"			return this._currentFormat;\n"\
"		};\n"\
"		this._setFormat = function (format) {\n"\
"			this._currentFormat = format.toLowerCase();\n"\
"		};\n"\
"		this.hasAlphaChannel = function () {\n"\
"			if (this.alphaChannel === 'auto') {\n"\
"				return (\n"\
"					this.format.toLowerCase() === 'any' || // format can change on the fly (e.g. from hex to rgba), so let's consider the alpha channel enabled\n"\
"					jsc.isAlphaFormat(this.getFormat()) || // the current format supports alpha channel\n"\
"					this.alpha !== undefined || // initial alpha value is set, so we're working with alpha channel\n"\
"					this.alphaElement !== undefined // the alpha value is redirected, so we're working with alpha channel\n"\
"				);\n"\
"			}\n"\
"			return this.alphaChannel; // the alpha channel is explicitly set\n"\
"		};\n"\
"		this.processValueInput = function (str) {\n"\
"			if (!this.fromString(str)) {\n"\
"				// could not parse the color value - let's just expose the current color\n"\
"				this.exposeColor();\n"\
"			}\n"\
"		};\n"\
"		this.processAlphaInput = function (str) {\n"\
"			if (!this.fromHSVA(null, null, null, parseFloat(str))) {\n"\
"				// could not parse the alpha value - let's just expose the current color\n"\
"				this.exposeColor();\n"\
"			}\n"\
"		};\n"\
"		this.exposeColor = function (flags) {\n"\
"			var colorStr = this.toString();\n"\
"			var fmt = this.getFormat();\n"\
"			// reflect current color in data- attribute\n"\
"			jsc.setDataAttr(this.targetElement, 'current-color', colorStr);\n"\
"			if (!(flags & jsc.flags.leaveValue) && this.valueElement) {\n"\
"				if (fmt === 'hex' || fmt === 'hexa') {\n"\
"					if (!this.uppercase) { colorStr = colorStr.toLowerCase(); }\n"\
"					if (!this.hash) { colorStr = colorStr.replace(/^#/, ''); }\n"\
"				}\n"\
"				this.setValueElementValue(colorStr);\n"\
"			}\n"\
"			if (!(flags & jsc.flags.leaveAlpha) && this.alphaElement) {\n"\
"				var alphaVal = Math.round(this.channels.a * 100) / 100;\n"\
"				this.setAlphaElementValue(alphaVal);\n"\
"			}\n"\
"			if (!(flags & jsc.flags.leavePreview) && this.previewElement) {\n"\
"				var previewPos = null; // 'left' | 'right' (null -> fill the entire element)\n"\
"				if (\n"\
"					jsc.isTextInput(this.previewElement) || // text input\n"\
"					(jsc.isButton(this.previewElement) && !jsc.isButtonEmpty(this.previewElement)) // button with text\n"\
"				) {\n"\
"					previewPos = this.previewPosition;\n"\
"				}\n"\
"				this.setPreviewElementBg(this.toRGBAString());\n"\
"			}\n"\
"			if (isPickerOwner()) {\n"\
"				redrawPad();\n"\
"				redrawSld();\n"\
"				redrawASld();\n"\
"			}\n"\
"		};\n"\
"		this.setPreviewElementBg = function (color) {\n"\
"			if (!this.previewElement) {\n"\
"				return;\n"\
"			}\n"\
"			var position = null; // color preview position:  null | 'left' | 'right'\n"\
"			var width = null; // color preview width:  px | null = fill the entire element\n"\
"			if (\n"\
"				jsc.isTextInput(this.previewElement) || // text input\n"\
"				(jsc.isButton(this.previewElement) && !jsc.isButtonEmpty(this.previewElement)) // button with text\n"\
"			) {\n"\
"				position = this.previewPosition;\n"\
"				width = this.previewSize;\n"\
"			}\n"\
"			var backgrounds = [];\n"\
"			if (!color) {\n"\
"				// there is no color preview to display -> let's remove any previous background image\n"\
"				backgrounds.push({\n"\
"					image: 'none',\n"\
"					position: 'left top',\n"\
"					size: 'auto',\n"\
"					repeat: 'no-repeat',\n"\
"					origin: 'padding-box',\n"\
"				});\n"\
"			} else {\n"\
"				// CSS gradient for background color preview\n"\
"				backgrounds.push({\n"\
"					image: jsc.genColorPreviewGradient(\n"\
"						color,\n"\
"						position,\n"\
"						width ? width - jsc.pub.previewSeparator.length : null\n"\
"					),\n"\
"					position: 'left top',\n"\
"					size: 'auto',\n"\
"					repeat: position ? 'repeat-y' : 'repeat',\n"\
"					origin: 'padding-box',\n"\
"				});\n"\
"				// data URL of generated PNG image with a gray transparency chessboard\n"\
"				var preview = jsc.genColorPreviewCanvas(\n"\
"					'rgba(0,0,0,0)',\n"\
"					position ? {'left':'right', 'right':'left'}[position] : null,\n"\
"					width,\n"\
"					true\n"\
"				);\n"\
"				backgrounds.push({\n"\
"					image: 'url(\\'' + preview.canvas.toDataURL() + '\\')',\n"\
"					position: (position || 'left') + ' top',\n"\
"					size: preview.width + 'px ' + preview.height + 'px',\n"\
"					repeat: position ? 'repeat-y' : 'repeat',\n"\
"					origin: 'padding-box',\n"\
"				});\n"\
"			}\n"\
"			var bg = {\n"\
"				image: [],\n"\
"				position: [],\n"\
"				size: [],\n"\
"				repeat: [],\n"\
"				origin: [],\n"\
"			};\n"\
"			for (var i = 0; i < backgrounds.length; i += 1) {\n"\
"				bg.image.push(backgrounds[i].image);\n"\
"				bg.position.push(backgrounds[i].position);\n"\
"				bg.size.push(backgrounds[i].size);\n"\
"				bg.repeat.push(backgrounds[i].repeat);\n"\
"				bg.origin.push(backgrounds[i].origin);\n"\
"			}\n"\
"			// set previewElement's background-images\n"\
"			var sty = {\n"\
"				'background-image': bg.image.join(', '),\n"\
"				'background-position': bg.position.join(', '),\n"\
"				'background-size': bg.size.join(', '),\n"\
"				'background-repeat': bg.repeat.join(', '),\n"\
"				'background-origin': bg.origin.join(', '),\n"\
"			};\n"\
"			jsc.setStyle(this.previewElement, sty, this.forceStyle);\n"\
"			// set/restore previewElement's padding\n"\
"			var padding = {\n"\
"				left: null,\n"\
"				right: null,\n"\
"			};\n"\
"			if (position) {\n"\
"				padding[position] = (this.previewSize + this.previewPadding) + 'px';\n"\
"			}\n"\
"			var sty = {\n"\
"				'padding-left': padding.left,\n"\
"				'padding-right': padding.right,\n"\
"			};\n"\
"			jsc.setStyle(this.previewElement, sty, this.forceStyle, true);\n"\
"		};\n"\
"		this.setValueElementValue = function (str) {\n"\
"			if (this.valueElement) {\n"\
"				if (jsc.nodeName(this.valueElement) === 'input') {\n"\
"					this.valueElement.value = str;\n"\
"				} else {\n"\
"					this.valueElement.innerHTML = str;\n"\
"				}\n"\
"			}\n"\
"		};\n"\
"		this.setAlphaElementValue = function (str) {\n"\
"			if (this.alphaElement) {\n"\
"				if (jsc.nodeName(this.alphaElement) === 'input') {\n"\
"					this.alphaElement.value = str;\n"\
"				} else {\n"\
"					this.alphaElement.innerHTML = str;\n"\
"				}\n"\
"			}\n"\
"		};\n"\
"		this._processParentElementsInDOM = function () {\n"\
"			if (this._parentElementsProcessed) { return; }\n"\
"			this._parentElementsProcessed = true;\n"\
"			var elm = this.targetElement;\n"\
"			do {\n"\
"				// If the target element or one of its parent nodes has fixed position,\n"\
"				// then use fixed positioning instead\n"\
"				var compStyle = jsc.getCompStyle(elm);\n"\
"				if (compStyle.position && compStyle.position.toLowerCase() === 'fixed') {\n"\
"					this.fixed = true;\n"\
"				}\n"\
"				if (elm !== this.targetElement) {\n"\
"					// Ensure to attach onParentScroll only once to each parent element\n"\
"					// (multiple targetElements can share the same parent nodes)\n"\
"					//\n"\
"					// Note: It's not just offsetParents that can be scrollable,\n"\
"					// that's why we loop through all parent nodes\n"\
"					if (!jsc.getData(elm, 'hasScrollListener')) {\n"\
"						elm.addEventListener('scroll', jsc.onParentScroll, false);\n"\
"						jsc.setData(elm, 'hasScrollListener', true);\n"\
"					}\n"\
"				}\n"\
"			} while ((elm = elm.parentNode) && jsc.nodeName(elm) !== 'body');\n"\
"		};\n"\
"		this.tryHide = function () {\n"\
"			if (this.hideOnLeave) {\n"\
"				this.hide();\n"\
"			}\n"\
"		};\n"\
"		this.set__palette = function (val) {\n"\
"			this.palette = val;\n"\
"			this._palette = jsc.parsePaletteValue(val);\n"\
"			this._paletteHasTransparency = jsc.containsTranparentColor(this._palette);\n"\
"		};\n"\
"		function setOption (option, value) {\n"\
"			if (typeof option !== 'string') {\n"\
"				throw new Error('Invalid value for option name: ' + option);\n"\
"			}\n"\
"			// enum option\n"\
"			if (jsc.enumOpts.hasOwnProperty(option)) {\n"\
"				if (typeof value === 'string') { // enum string values are case insensitive\n"\
"					value = value.toLowerCase();\n"\
"				}\n"\
"				if (jsc.enumOpts[option].indexOf(value) === -1) {\n"\
"					throw new Error('Option \\'' + option + '\\' has invalid value: ' + value);\n"\
"				}\n"\
"			}\n"\
"			// deprecated option\n"\
"			if (jsc.deprecatedOpts.hasOwnProperty(option)) {\n"\
"				var oldOpt = option;\n"\
"				var newOpt = jsc.deprecatedOpts[option];\n"\
"				if (newOpt) {\n"\
"					// if we have a new name for this option, let's log a warning and use the new name\n"\
"					console.warn('Option \\'%s\\' is DEPRECATED, using \\'%s\\' instead.' + jsc.docsRef, oldOpt, newOpt);\n"\
"					option = newOpt;\n"\
"				} else {\n"\
"					// new name not available for the option\n"\
"					throw new Error('Option \\'' + option + '\\' is DEPRECATED');\n"\
"				}\n"\
"			}\n"\
"			var setter = 'set__' + option;\n"\
"			if (typeof THIS[setter] === 'function') { // a setter exists for this option\n"\
"				THIS[setter](value);\n"\
"				return true;\n"\
"			} else if (option in THIS) { // option exists as a property\n"\
"				THIS[option] = value;\n"\
"				return true;\n"\
"			}\n"\
"			throw new Error('Unrecognized configuration option: ' + option);\n"\
"		}\n"\
"		function getOption (option) {\n"\
"			if (typeof option !== 'string') {\n"\
"				throw new Error('Invalid value for option name: ' + option);\n"\
"			}\n"\
"			// deprecated option\n"\
"			if (jsc.deprecatedOpts.hasOwnProperty(option)) {\n"\
"				var oldOpt = option;\n"\
"				var newOpt = jsc.deprecatedOpts[option];\n"\
"				if (newOpt) {\n"\
"					// if we have a new name for this option, let's log a warning and use the new name\n"\
"					console.warn('Option \\'%s\\' is DEPRECATED, using \\'%s\\' instead.' + jsc.docsRef, oldOpt, newOpt);\n"\
"					option = newOpt;\n"\
"				} else {\n"\
"					// new name not available for the option\n"\
"					throw new Error('Option \\'' + option + '\\' is DEPRECATED');\n"\
"				}\n"\
"			}\n"\
"			var getter = 'get__' + option;\n"\
"			if (typeof THIS[getter] === 'function') { // a getter exists for this option\n"\
"				return THIS[getter](value);\n"\
"			} else if (option in THIS) { // option exists as a property\n"\
"				return THIS[option];\n"\
"			}\n"\
"			throw new Error('Unrecognized configuration option: ' + option);\n"\
"		}\n"\
"		function detachPicker () {\n"\
"			jsc.removeClass(THIS.targetElement, jsc.pub.activeClassName);\n"\
"			jsc.picker.wrap.parentNode.removeChild(jsc.picker.wrap);\n"\
"			delete jsc.picker.owner;\n"\
"		}\n"\
"		function drawPicker () {\n"\
"			// At this point, when drawing the picker, we know what the parent elements are\n"\
"			// and we can do all related DOM operations, such as registering events on them\n"\
"			// or checking their positioning\n"\
"			THIS._processParentElementsInDOM();\n"\
"			if (!jsc.picker) {\n"\
"				jsc.picker = {\n"\
"					owner: null, // owner picker instance\n"\
"					wrap : jsc.createEl('div'),\n"\
"					box : jsc.createEl('div'),\n"\
"					boxS : jsc.createEl('div'), // shadow area\n"\
"					boxB : jsc.createEl('div'), // border\n"\
"					pad : jsc.createEl('div'),\n"\
"					padB : jsc.createEl('div'), // border\n"\
"					padM : jsc.createEl('div'), // mouse/touch area\n"\
"					padCanvas : jsc.createPadCanvas(),\n"\
"					cross : jsc.createEl('div'),\n"\
"					crossBY : jsc.createEl('div'), // border Y\n"\
"					crossBX : jsc.createEl('div'), // border X\n"\
"					crossLY : jsc.createEl('div'), // line Y\n"\
"					crossLX : jsc.createEl('div'), // line X\n"\
"					sld : jsc.createEl('div'), // slider\n"\
"					sldB : jsc.createEl('div'), // border\n"\
"					sldM : jsc.createEl('div'), // mouse/touch area\n"\
"					sldGrad : jsc.createSliderGradient(),\n"\
"					sldPtrS : jsc.createEl('div'), // slider pointer spacer\n"\
"					sldPtrIB : jsc.createEl('div'), // slider pointer inner border\n"\
"					sldPtrMB : jsc.createEl('div'), // slider pointer middle border\n"\
"					sldPtrOB : jsc.createEl('div'), // slider pointer outer border\n"\
"					asld : jsc.createEl('div'), // alpha slider\n"\
"					asldB : jsc.createEl('div'), // border\n"\
"					asldM : jsc.createEl('div'), // mouse/touch area\n"\
"					asldGrad : jsc.createASliderGradient(),\n"\
"					asldPtrS : jsc.createEl('div'), // slider pointer spacer\n"\
"					asldPtrIB : jsc.createEl('div'), // slider pointer inner border\n"\
"					asldPtrMB : jsc.createEl('div'), // slider pointer middle border\n"\
"					asldPtrOB : jsc.createEl('div'), // slider pointer outer border\n"\
"					pal : jsc.createEl('div'), // palette\n"\
"					btn : jsc.createEl('div'),\n"\
"					btnT : jsc.createEl('span'), // text\n"\
"				};\n"\
"				jsc.picker.pad.appendChild(jsc.picker.padCanvas.elm);\n"\
"				jsc.picker.padB.appendChild(jsc.picker.pad);\n"\
"				jsc.picker.cross.appendChild(jsc.picker.crossBY);\n"\
"				jsc.picker.cross.appendChild(jsc.picker.crossBX);\n"\
"				jsc.picker.cross.appendChild(jsc.picker.crossLY);\n"\
"				jsc.picker.cross.appendChild(jsc.picker.crossLX);\n"\
"				jsc.picker.padB.appendChild(jsc.picker.cross);\n"\
"				jsc.picker.box.appendChild(jsc.picker.padB);\n"\
"				jsc.picker.box.appendChild(jsc.picker.padM);\n"\
"				jsc.picker.sld.appendChild(jsc.picker.sldGrad.elm);\n"\
"				jsc.picker.sldB.appendChild(jsc.picker.sld);\n"\
"				jsc.picker.sldB.appendChild(jsc.picker.sldPtrOB);\n"\
"				jsc.picker.sldPtrOB.appendChild(jsc.picker.sldPtrMB);\n"\
"				jsc.picker.sldPtrMB.appendChild(jsc.picker.sldPtrIB);\n"\
"				jsc.picker.sldPtrIB.appendChild(jsc.picker.sldPtrS);\n"\
"				jsc.picker.box.appendChild(jsc.picker.sldB);\n"\
"				jsc.picker.box.appendChild(jsc.picker.sldM);\n"\
"				jsc.picker.asld.appendChild(jsc.picker.asldGrad.elm);\n"\
"				jsc.picker.asldB.appendChild(jsc.picker.asld);\n"\
"				jsc.picker.asldB.appendChild(jsc.picker.asldPtrOB);\n"\
"				jsc.picker.asldPtrOB.appendChild(jsc.picker.asldPtrMB);\n"\
"				jsc.picker.asldPtrMB.appendChild(jsc.picker.asldPtrIB);\n"\
"				jsc.picker.asldPtrIB.appendChild(jsc.picker.asldPtrS);\n"\
"				jsc.picker.box.appendChild(jsc.picker.asldB);\n"\
"				jsc.picker.box.appendChild(jsc.picker.asldM);\n"\
"				jsc.picker.box.appendChild(jsc.picker.pal);\n"\
"				jsc.picker.btn.appendChild(jsc.picker.btnT);\n"\
"				jsc.picker.box.appendChild(jsc.picker.btn);\n"\
"				jsc.picker.boxB.appendChild(jsc.picker.box);\n"\
"				jsc.picker.wrap.appendChild(jsc.picker.boxS);\n"\
"				jsc.picker.wrap.appendChild(jsc.picker.boxB);\n"\
"				jsc.picker.wrap.addEventListener('touchstart', jsc.onPickerTouchStart,\n"\
"					jsc.isPassiveEventSupported ? {passive: false} : false);\n"\
"			}\n"\
"			var p = jsc.picker;\n"\
"			var displaySlider = !!jsc.getSliderChannel(THIS);\n"\
"			var displayAlphaSlider = THIS.hasAlphaChannel();\n"\
"			var pickerDims = jsc.getPickerDims(THIS);\n"\
"			var crossOuterSize = (2 * THIS.pointerBorderWidth + THIS.pointerThickness + 2 * THIS.crossSize);\n"\
"			var controlPadding = jsc.getControlPadding(THIS);\n"\
"			var borderRadius = Math.min(\n"\
"				THIS.borderRadius,\n"\
"				Math.round(THIS.padding * Math.PI)); // px\n"\
"			var padCursor = 'crosshair';\n"\
"			// wrap\n"\
"			p.wrap.className = 'jscolor-picker-wrap';\n"\
"			p.wrap.style.clear = 'both';\n"\
"			p.wrap.style.width = pickerDims.borderW + 'px';\n"\
"			p.wrap.style.height = pickerDims.borderH + 'px';\n"\
"			p.wrap.style.zIndex = THIS.zIndex;\n"\
"			// picker\n"\
"			p.box.className = 'jscolor-picker';\n"\
"			p.box.style.width = pickerDims.paddedW + 'px';\n"\
"			p.box.style.height = pickerDims.paddedH + 'px';\n"\
"			p.box.style.position = 'relative';\n"\
"			// picker shadow\n"\
"			p.boxS.className = 'jscolor-picker-shadow';\n"\
"			p.boxS.style.position = 'absolute';\n"\
"			p.boxS.style.left = '0';\n"\
"			p.boxS.style.top = '0';\n"\
"			p.boxS.style.width = '100%';\n"\
"			p.boxS.style.height = '100%';\n"\
"			jsc.setBorderRadius(p.boxS, borderRadius + 'px');\n"\
"			// picker border\n"\
"			p.boxB.className = 'jscolor-picker-border';\n"\
"			p.boxB.style.position = 'relative';\n"\
"			p.boxB.style.border = THIS.borderWidth + 'px solid';\n"\
"			p.boxB.style.borderColor = THIS.borderColor;\n"\
"			p.boxB.style.background = THIS.backgroundColor;\n"\
"			jsc.setBorderRadius(p.boxB, borderRadius + 'px');\n"\
"			// IE hack:\n"\
"			// If the element is transparent, IE will trigger the event on the elements under it,\n"\
"			// e.g. on Canvas or on elements with border\n"\
"			p.padM.style.background = 'rgba(255,0,0,.2)';\n"\
"			p.sldM.style.background = 'rgba(0,255,0,.2)';\n"\
"			p.asldM.style.background = 'rgba(0,0,255,.2)';\n"\
"			p.padM.style.opacity =\n"\
"			p.sldM.style.opacity =\n"\
"			p.asldM.style.opacity =\n"\
"				'0';\n"\
"			// pad\n"\
"			p.pad.style.position = 'relative';\n"\
"			p.pad.style.width = THIS.width + 'px';\n"\
"			p.pad.style.height = THIS.height + 'px';\n"\
"			// pad - color spectrum (HSV and HVS)\n"\
"			p.padCanvas.draw(THIS.width, THIS.height, jsc.getPadYChannel(THIS));\n"\
"			// pad border\n"\
"			p.padB.style.position = 'absolute';\n"\
"			p.padB.style.left = THIS.padding + 'px';\n"\
"			p.padB.style.top = THIS.padding + 'px';\n"\
"			p.padB.style.border = THIS.controlBorderWidth + 'px solid';\n"\
"			p.padB.style.borderColor = THIS.controlBorderColor;\n"\
"			// pad mouse area\n"\
"			p.padM.style.position = 'absolute';\n"\
"			p.padM.style.left = 0 + 'px';\n"\
"			p.padM.style.top = 0 + 'px';\n"\
"			p.padM.style.width = (THIS.padding + 2 * THIS.controlBorderWidth + THIS.width + controlPadding) + 'px';\n"\
"			p.padM.style.height = (2 * THIS.controlBorderWidth + 2 * THIS.padding + THIS.height) + 'px';\n"\
"			p.padM.style.cursor = padCursor;\n"\
"			jsc.setData(p.padM, {\n"\
"				instance: THIS,\n"\
"				control: 'pad',\n"\
"			})\n"\
"			// pad cross\n"\
"			p.cross.style.position = 'absolute';\n"\
"			p.cross.style.left =\n"\
"			p.cross.style.top =\n"\
"				'0';\n"\
"			p.cross.style.width =\n"\
"			p.cross.style.height =\n"\
"				crossOuterSize + 'px';\n"\
"			// pad cross border Y and X\n"\
"			p.crossBY.style.position =\n"\
"			p.crossBX.style.position =\n"\
"				'absolute';\n"\
"			p.crossBY.style.background =\n"\
"			p.crossBX.style.background =\n"\
"				THIS.pointerBorderColor;\n"\
"			p.crossBY.style.width =\n"\
"			p.crossBX.style.height =\n"\
"				(2 * THIS.pointerBorderWidth + THIS.pointerThickness) + 'px';\n"\
"			p.crossBY.style.height =\n"\
"			p.crossBX.style.width =\n"\
"				crossOuterSize + 'px';\n"\
"			p.crossBY.style.left =\n"\
"			p.crossBX.style.top =\n"\
"				(Math.floor(crossOuterSize / 2) - Math.floor(THIS.pointerThickness / 2) - THIS.pointerBorderWidth) + 'px';\n"\
"			p.crossBY.style.top =\n"\
"			p.crossBX.style.left =\n"\
"				'0';\n"\
"			// pad cross line Y and X\n"\
"			p.crossLY.style.position =\n"\
"			p.crossLX.style.position =\n"\
"				'absolute';\n"\
"			p.crossLY.style.background =\n"\
"			p.crossLX.style.background =\n"\
"				THIS.pointerColor;\n"\
"			p.crossLY.style.height =\n"\
"			p.crossLX.style.width =\n"\
"				(crossOuterSize - 2 * THIS.pointerBorderWidth) + 'px';\n"\
"			p.crossLY.style.width =\n"\
"			p.crossLX.style.height =\n"\
"				THIS.pointerThickness + 'px';\n"\
"			p.crossLY.style.left =\n"\
"			p.crossLX.style.top =\n"\
"				(Math.floor(crossOuterSize / 2) - Math.floor(THIS.pointerThickness / 2)) + 'px';\n"\
"			p.crossLY.style.top =\n"\
"			p.crossLX.style.left =\n"\
"				THIS.pointerBorderWidth + 'px';\n"\
"			// slider\n"\
"			p.sld.style.overflow = 'hidden';\n"\
"			p.sld.style.width = THIS.sliderSize + 'px';\n"\
"			p.sld.style.height = THIS.height + 'px';\n"\
"			// slider gradient\n"\
"			p.sldGrad.draw(THIS.sliderSize, THIS.height, '#000', '#000');\n"\
"			// slider border\n"\
"			p.sldB.style.display = displaySlider ? 'block' : 'none';\n"\
"			p.sldB.style.position = 'absolute';\n"\
"			p.sldB.style.left = (THIS.padding + THIS.width + 2 * THIS.controlBorderWidth + 2 * controlPadding) + 'px';\n"\
"			p.sldB.style.top = THIS.padding + 'px';\n"\
"			p.sldB.style.border = THIS.controlBorderWidth + 'px solid';\n"\
"			p.sldB.style.borderColor = THIS.controlBorderColor;\n"\
"			// slider mouse area\n"\
"			p.sldM.style.display = displaySlider ? 'block' : 'none';\n"\
"			p.sldM.style.position = 'absolute';\n"\
"			p.sldM.style.left = (THIS.padding + THIS.width + 2 * THIS.controlBorderWidth + controlPadding) + 'px';\n"\
"			p.sldM.style.top = 0 + 'px';\n"\
"			p.sldM.style.width = (\n"\
"					(THIS.sliderSize + 2 * controlPadding + 2 * THIS.controlBorderWidth) +\n"\
"					(displayAlphaSlider ? 0 : Math.max(0, THIS.padding - controlPadding)) // remaining padding to the right edge\n"\
"				) + 'px';\n"\
"			p.sldM.style.height = (2 * THIS.controlBorderWidth + 2 * THIS.padding + THIS.height) + 'px';\n"\
"			p.sldM.style.cursor = 'default';\n"\
"			jsc.setData(p.sldM, {\n"\
"				instance: THIS,\n"\
"				control: 'sld',\n"\
"			});\n"\
"			// slider pointer inner and outer border\n"\
"			p.sldPtrIB.style.border =\n"\
"			p.sldPtrOB.style.border =\n"\
"				THIS.pointerBorderWidth + 'px solid ' + THIS.pointerBorderColor;\n"\
"			// slider pointer outer border\n"\
"			p.sldPtrOB.style.position = 'absolute';\n"\
"			p.sldPtrOB.style.left = -(2 * THIS.pointerBorderWidth + THIS.pointerThickness) + 'px';\n"\
"			p.sldPtrOB.style.top = '0';\n"\
"			// slider pointer middle border\n"\
"			p.sldPtrMB.style.border = THIS.pointerThickness + 'px solid ' + THIS.pointerColor;\n"\
"			// slider pointer spacer\n"\
"			p.sldPtrS.style.width = THIS.sliderSize + 'px';\n"\
"			p.sldPtrS.style.height = jsc.pub.sliderInnerSpace + 'px';\n"\
"			// alpha slider\n"\
"			p.asld.style.overflow = 'hidden';\n"\
"			p.asld.style.width = THIS.sliderSize + 'px';\n"\
"			p.asld.style.height = THIS.height + 'px';\n"\
"			// alpha slider gradient\n"\
"			p.asldGrad.draw(THIS.sliderSize, THIS.height, '#000');\n"\
"			// alpha slider border\n"\
"			p.asldB.style.display = displayAlphaSlider ? 'block' : 'none';\n"\
"			p.asldB.style.position = 'absolute';\n"\
"			p.asldB.style.left = (\n"\
"					(THIS.padding + THIS.width + 2 * THIS.controlBorderWidth + controlPadding) +\n"\
"					(displaySlider ? (THIS.sliderSize + 3 * controlPadding + 2 * THIS.controlBorderWidth) : 0)\n"\
"				) + 'px';\n"\
"			p.asldB.style.top = THIS.padding + 'px';\n"\
"			p.asldB.style.border = THIS.controlBorderWidth + 'px solid';\n"\
"			p.asldB.style.borderColor = THIS.controlBorderColor;\n"\
"			// alpha slider mouse area\n"\
"			p.asldM.style.display = displayAlphaSlider ? 'block' : 'none';\n"\
"			p.asldM.style.position = 'absolute';\n"\
"			p.asldM.style.left = (\n"\
"					(THIS.padding + THIS.width + 2 * THIS.controlBorderWidth + controlPadding) +\n"\
"					(displaySlider ? (THIS.sliderSize + 2 * controlPadding + 2 * THIS.controlBorderWidth) : 0)\n"\
"				) + 'px';\n"\
"			p.asldM.style.top = 0 + 'px';\n"\
"			p.asldM.style.width = (\n"\
"					(THIS.sliderSize + 2 * controlPadding + 2 * THIS.controlBorderWidth) +\n"\
"					Math.max(0, THIS.padding - controlPadding) // remaining padding to the right edge\n"\
"				) + 'px';\n"\
"			p.asldM.style.height = (2 * THIS.controlBorderWidth + 2 * THIS.padding + THIS.height) + 'px';\n"\
"			p.asldM.style.cursor = 'default';\n"\
"			jsc.setData(p.asldM, {\n"\
"				instance: THIS,\n"\
"				control: 'asld',\n"\
"			})\n"\
"			// alpha slider pointer inner and outer border\n"\
"			p.asldPtrIB.style.border =\n"\
"			p.asldPtrOB.style.border =\n"\
"				THIS.pointerBorderWidth + 'px solid ' + THIS.pointerBorderColor;\n"\
"			// alpha slider pointer outer border\n"\
"			p.asldPtrOB.style.position = 'absolute';\n"\
"			p.asldPtrOB.style.left = -(2 * THIS.pointerBorderWidth + THIS.pointerThickness) + 'px';\n"\
"			p.asldPtrOB.style.top = '0';\n"\
"			// alpha slider pointer middle border\n"\
"			p.asldPtrMB.style.border = THIS.pointerThickness + 'px solid ' + THIS.pointerColor;\n"\
"			// alpha slider pointer spacer\n"\
"			p.asldPtrS.style.width = THIS.sliderSize + 'px';\n"\
"			p.asldPtrS.style.height = jsc.pub.sliderInnerSpace + 'px';\n"\
"			// palette\n"\
"			p.pal.className = 'jscolor-palette';\n"\
"			p.pal.style.display = pickerDims.palette.rows ? 'block' : 'none';\n"\
"			p.pal.style.position = 'absolute';\n"\
"			p.pal.style.left = THIS.padding + 'px';\n"\
"			p.pal.style.top = (2 * THIS.controlBorderWidth + 2 * THIS.padding + THIS.height) + 'px';\n"\
"			// palette's color samples\n"\
"			p.pal.innerHTML = '';\n"\
"			var chessboard = jsc.genColorPreviewCanvas('rgba(0,0,0,0)');\n"\
"			var si = 0; // color sample's index\n"\
"			for (var r = 0; r < pickerDims.palette.rows; r++) {\n"\
"				for (var c = 0; c < pickerDims.palette.cols && si < THIS._palette.length; c++, si++) {\n"\
"					var sampleColor = THIS._palette[si];\n"\
"					var sampleCssColor = jsc.rgbaColor.apply(null, sampleColor.rgba);\n"\
"					var sc = jsc.createEl('div'); // color sample's color\n"\
"					sc.style.width = (pickerDims.palette.cellW - 2 * THIS.controlBorderWidth) + 'px';\n"\
"					sc.style.height = (pickerDims.palette.cellH - 2 * THIS.controlBorderWidth) + 'px';\n"\
"					sc.style.backgroundColor = sampleCssColor;\n"\
"					var sw = jsc.createEl('div'); // color sample's wrap\n"\
"					sw.className = 'jscolor-palette-sample';\n"\
"					sw.style.display = 'block';\n"\
"					sw.style.position = 'absolute';\n"\
"					sw.style.left = (\n"\
"							pickerDims.palette.cols <= 1 ? 0 :\n"\
"							Math.round(10 * (c * ((pickerDims.contentW - pickerDims.palette.cellW) / (pickerDims.palette.cols - 1)))) / 10\n"\
"						) + 'px';\n"\
"					sw.style.top = (r * (pickerDims.palette.cellH + THIS.paletteSpacing)) + 'px';\n"\
"					sw.style.border = THIS.controlBorderWidth + 'px solid';\n"\
"					sw.style.borderColor = THIS.controlBorderColor;\n"\
"					sw.style.cursor = 'pointer';\n"\
"					if (sampleColor.rgba[3] !== null && sampleColor.rgba[3] < 1.0) { // only create chessboard background if the sample has transparency\n"\
"						sw.style.backgroundImage = 'url(\\'' + chessboard.canvas.toDataURL() + '\\')';\n"\
"						sw.style.backgroundRepeat = 'repeat';\n"\
"						sw.style.backgroundPosition = 'center center';\n"\
"					}\n"\
"					jsc.setData(sw, {\n"\
"						instance: THIS,\n"\
"						control: 'palette-sample',\n"\
"						color: sampleColor,\n"\
"					})\n"\
"					sw.addEventListener('click', jsc.onPaletteSampleClick, false);\n"\
"					sw.appendChild(sc);\n"\
"					p.pal.appendChild(sw);\n"\
"				}\n"\
"			}\n"\
"			// the Close button\n"\
"			function setBtnBorder () {\n"\
"				var insetColors = THIS.controlBorderColor.split(/\\s+/);\n"\
"				var outsetColor = insetColors.length < 2 ? insetColors[0] : insetColors[1] + ' ' + insetColors[0] + ' ' + insetColors[0] + ' ' + insetColors[1];\n"\
"				p.btn.style.borderColor = outsetColor;\n"\
"			}\n"\
"			var btnPadding = 15; // px\n"\
"			p.btn.className = 'jscolor-btn-close';\n"\
"			p.btn.style.display = THIS.closeButton ? 'block' : 'none';\n"\
"			p.btn.style.position = 'absolute';\n"\
"			p.btn.style.left = THIS.padding + 'px';\n"\
"			p.btn.style.bottom = THIS.padding + 'px';\n"\
"			p.btn.style.padding = '0 ' + btnPadding + 'px';\n"\
"			p.btn.style.maxWidth = (pickerDims.contentW - 2 * THIS.controlBorderWidth - 2 * btnPadding) + 'px';\n"\
"			p.btn.style.overflow = 'hidden';\n"\
"			p.btn.style.height = THIS.buttonHeight + 'px';\n"\
"			p.btn.style.whiteSpace = 'nowrap';\n"\
"			p.btn.style.border = THIS.controlBorderWidth + 'px solid';\n"\
"			setBtnBorder();\n"\
"			p.btn.style.color = THIS.buttonColor;\n"\
"			p.btn.style.font = '12px sans-serif';\n"\
"			p.btn.style.textAlign = 'center';\n"\
"			p.btn.style.cursor = 'pointer';\n"\
"			p.btn.onmousedown = function () {\n"\
"				THIS.hide();\n"\
"			};\n"\
"			p.btnT.style.lineHeight = THIS.buttonHeight + 'px';\n"\
"			p.btnT.innerHTML = '';\n"\
"			p.btnT.appendChild(window.document.createTextNode(THIS.closeText));\n"\
"			// reposition the pointers\n"\
"			redrawPad();\n"\
"			redrawSld();\n"\
"			redrawASld();\n"\
"			// If we are changing the owner without first closing the picker,\n"\
"			// make sure to first deal with the old owner\n"\
"			if (jsc.picker.owner && jsc.picker.owner !== THIS) {\n"\
"				jsc.removeClass(jsc.picker.owner.targetElement, jsc.pub.activeClassName);\n"\
"			}\n"\
"			// Set a new picker owner\n"\
"			jsc.picker.owner = THIS;\n"\
"			// The redrawPosition() method needs picker.owner to be set, that's why we call it here,\n"\
"			// after setting the owner\n"\
"			if (THIS.container === window.document.body) {\n"\
"				jsc.redrawPosition();\n"\
"			} else {\n"\
"				jsc._drawPosition(THIS, 0, 0, 'relative', false);\n"\
"			}\n"\
"			if (p.wrap.parentNode !== THIS.container) {\n"\
"				THIS.container.appendChild(p.wrap);\n"\
"			}\n"\
"			jsc.addClass(THIS.targetElement, jsc.pub.activeClassName);\n"\
"		}\n"\
"		function redrawPad () {\n"\
"			// redraw the pad pointer\n"\
"			var yChannel = jsc.getPadYChannel(THIS);\n"\
"			var x = Math.round((THIS.channels.h / 360) * (THIS.width - 1));\n"\
"			var y = Math.round((1 - THIS.channels[yChannel] / 100) * (THIS.height - 1));\n"\
"			var crossOuterSize = (2 * THIS.pointerBorderWidth + THIS.pointerThickness + 2 * THIS.crossSize);\n"\
"			var ofs = -Math.floor(crossOuterSize / 2);\n"\
"			jsc.picker.cross.style.left = (x + ofs) + 'px';\n"\
"			jsc.picker.cross.style.top = (y + ofs) + 'px';\n"\
"			// redraw the slider\n"\
"			switch (jsc.getSliderChannel(THIS)) {\n"\
"			case 's':\n"\
"				var rgb1 = jsc.HSV_RGB(THIS.channels.h, 100, THIS.channels.v);\n"\
"				var rgb2 = jsc.HSV_RGB(THIS.channels.h, 0, THIS.channels.v);\n"\
"				var color1 = 'rgb(' +\n"\
"					Math.round(rgb1[0]) + ',' +\n"\
"					Math.round(rgb1[1]) + ',' +\n"\
"					Math.round(rgb1[2]) + ')';\n"\
"				var color2 = 'rgb(' +\n"\
"					Math.round(rgb2[0]) + ',' +\n"\
"					Math.round(rgb2[1]) + ',' +\n"\
"					Math.round(rgb2[2]) + ')';\n"\
"				jsc.picker.sldGrad.draw(THIS.sliderSize, THIS.height, color1, color2);\n"\
"				break;\n"\
"			case 'v':\n"\
"				var rgb = jsc.HSV_RGB(THIS.channels.h, THIS.channels.s, 100);\n"\
"				var color1 = 'rgb(' +\n"\
"					Math.round(rgb[0]) + ',' +\n"\
"					Math.round(rgb[1]) + ',' +\n"\
"					Math.round(rgb[2]) + ')';\n"\
"				var color2 = '#000';\n"\
"				jsc.picker.sldGrad.draw(THIS.sliderSize, THIS.height, color1, color2);\n"\
"				break;\n"\
"			}\n"\
"			// redraw the alpha slider\n"\
"			jsc.picker.asldGrad.draw(THIS.sliderSize, THIS.height, THIS.toHEXString());\n"\
"		}\n"\
"		function redrawSld () {\n"\
"			var sldChannel = jsc.getSliderChannel(THIS);\n"\
"			if (sldChannel) {\n"\
"				// redraw the slider pointer\n"\
"				var y = Math.round((1 - THIS.channels[sldChannel] / 100) * (THIS.height - 1));\n"\
"				jsc.picker.sldPtrOB.style.top = (y - (2 * THIS.pointerBorderWidth + THIS.pointerThickness) - Math.floor(jsc.pub.sliderInnerSpace / 2)) + 'px';\n"\
"			}\n"\
"			// redraw the alpha slider\n"\
"			jsc.picker.asldGrad.draw(THIS.sliderSize, THIS.height, THIS.toHEXString());\n"\
"		}\n"\
"		function redrawASld () {\n"\
"			var y = Math.round((1 - THIS.channels.a) * (THIS.height - 1));\n"\
"			jsc.picker.asldPtrOB.style.top = (y - (2 * THIS.pointerBorderWidth + THIS.pointerThickness) - Math.floor(jsc.pub.sliderInnerSpace / 2)) + 'px';\n"\
"		}\n"\
"		function isPickerOwner () {\n"\
"			return jsc.picker && jsc.picker.owner === THIS;\n"\
"		}\n"\
"		function onValueKeyDown (ev) {\n"\
"			if (jsc.eventKey(ev) === 'Enter') {\n"\
"				if (THIS.valueElement) {\n"\
"					THIS.processValueInput(THIS.valueElement.value);\n"\
"				}\n"\
"				THIS.tryHide();\n"\
"			}\n"\
"		}\n"\
"		function onAlphaKeyDown (ev) {\n"\
"			if (jsc.eventKey(ev) === 'Enter') {\n"\
"				if (THIS.alphaElement) {\n"\
"					THIS.processAlphaInput(THIS.alphaElement.value);\n"\
"				}\n"\
"				THIS.tryHide();\n"\
"			}\n"\
"		}\n"\
"		function onValueChange (ev) {\n"\
"			if (jsc.getData(ev, 'internal')) {\n"\
"				return; // skip if the event was internally triggered by jscolor\n"\
"			}\n"\
"			var oldVal = THIS.valueElement.value;\n"\
"			THIS.processValueInput(THIS.valueElement.value); // this might change the value\n"\
"			jsc.triggerCallback(THIS, 'onChange');\n"\
"			if (THIS.valueElement.value !== oldVal) {\n"\
"				// value was additionally changed -> let's trigger the change event again, even though it was natively dispatched\n"\
"				jsc.triggerInputEvent(THIS.valueElement, 'change', true, true);\n"\
"			}\n"\
"		}\n"\
"		function onAlphaChange (ev) {\n"\
"			if (jsc.getData(ev, 'internal')) {\n"\
"				return; // skip if the event was internally triggered by jscolor\n"\
"			}\n"\
"			var oldVal = THIS.alphaElement.value;\n"\
"			THIS.processAlphaInput(THIS.alphaElement.value); // this might change the value\n"\
"			jsc.triggerCallback(THIS, 'onChange');\n"\
"			// triggering valueElement's onChange (because changing alpha changes the entire color, e.g. with rgba format)\n"\
"			jsc.triggerInputEvent(THIS.valueElement, 'change', true, true);\n"\
"			if (THIS.alphaElement.value !== oldVal) {\n"\
"				// value was additionally changed -> let's trigger the change event again, even though it was natively dispatched\n"\
"				jsc.triggerInputEvent(THIS.alphaElement, 'change', true, true);\n"\
"			}\n"\
"		}\n"\
"		function onValueInput (ev) {\n"\
"			if (jsc.getData(ev, 'internal')) {\n"\
"				return; // skip if the event was internally triggered by jscolor\n"\
"			}\n"\
"			if (THIS.valueElement) {\n"\
"				THIS.fromString(THIS.valueElement.value, jsc.flags.leaveValue);\n"\
"			}\n"\
"			jsc.triggerCallback(THIS, 'onInput');\n"\
"			// triggering valueElement's onInput\n"\
"			// (not needed, it was dispatched normally by the browser)\n"\
"		}\n"\
"		function onAlphaInput (ev) {\n"\
"			if (jsc.getData(ev, 'internal')) {\n"\
"				return; // skip if the event was internally triggered by jscolor\n"\
"			}\n"\
"			if (THIS.alphaElement) {\n"\
"				THIS.fromHSVA(null, null, null, parseFloat(THIS.alphaElement.value), jsc.flags.leaveAlpha);\n"\
"			}\n"\
"			jsc.triggerCallback(THIS, 'onInput');\n"\
"			// triggering valueElement's onInput (because changing alpha changes the entire color, e.g. with rgba format)\n"\
"			jsc.triggerInputEvent(THIS.valueElement, 'input', true, true);\n"\
"		}\n"\
"		// let's process the DEPRECATED 'options' property (this will be later removed)\n"\
"		if (jsc.pub.options) {\n"\
"			// let's set custom default options, if specified\n"\
"			for (var opt in jsc.pub.options) {\n"\
"				if (jsc.pub.options.hasOwnProperty(opt)) {\n"\
"					try {\n"\
"						setOption(opt, jsc.pub.options[opt]);\n"\
"					} catch (e) {\n"\
"						console.warn(e);\n"\
"					}\n"\
"				}\n"\
"			}\n"\
"		}\n"\
"		// let's apply configuration presets\n"\
"		//\n"\
"		var presetsArr = [];\n"\
"		if (opts.preset) {\n"\
"			if (typeof opts.preset === 'string') {\n"\
"				presetsArr = opts.preset.split(/\\s+/);\n"\
"			} else if (Array.isArray(opts.preset)) {\n"\
"				presetsArr = opts.preset.slice(); // slice() to clone\n"\
"			} else {\n"\
"				console.warn('Unrecognized preset value');\n"\
"			}\n"\
"		}\n"\
"		// always use the 'default' preset. If it's not listed, append it to the end.\n"\
"		if (presetsArr.indexOf('default') === -1) {\n"\
"			presetsArr.push('default');\n"\
"		}\n"\
"		// let's apply the presets in reverse order, so that should there be any overlapping options,\n"\
"		// the formerly listed preset will override the latter\n"\
"		for (var i = presetsArr.length - 1; i >= 0; i -= 1) {\n"\
"			var pres = presetsArr[i];\n"\
"			if (!pres) {\n"\
"				continue; // preset is empty string\n"\
"			}\n"\
"			if (!jsc.pub.presets.hasOwnProperty(pres)) {\n"\
"				console.warn('Unknown preset: %s', pres);\n"\
"				continue;\n"\
"			}\n"\
"			for (var opt in jsc.pub.presets[pres]) {\n"\
"				if (jsc.pub.presets[pres].hasOwnProperty(opt)) {\n"\
"					try {\n"\
"						setOption(opt, jsc.pub.presets[pres][opt]);\n"\
"					} catch (e) {\n"\
"						console.warn(e);\n"\
"					}\n"\
"				}\n"\
"			}\n"\
"		}\n"\
"		// let's set specific options for this color picker\n"\
"		var nonProperties = [\n"\
"			// these options won't be set as instance properties\n"\
"			'preset',\n"\
"		];\n"\
"		for (var opt in opts) {\n"\
"			if (opts.hasOwnProperty(opt)) {\n"\
"				if (nonProperties.indexOf(opt) === -1) {\n"\
"					try {\n"\
"						setOption(opt, opts[opt]);\n"\
"					} catch (e) {\n"\
"						console.warn(e);\n"\
"					}\n"\
"				}\n"\
"			}\n"\
"		}\n"\
"		//\n"\
"		// Install the color picker on chosen element(s)\n"\
"		//\n"\
"		// Determine picker's container element\n"\
"		if (this.container === undefined) {\n"\
"			this.container = window.document.body; // default container is BODY element\n"\
"		} else { // explicitly set to custom element\n"\
"			this.container = jsc.node(this.container);\n"\
"		}\n"\
"		if (!this.container) {\n"\
"			throw new Error('Cannot instantiate color picker without a container element');\n"\
"		}\n"\
"		// Fetch the target element\n"\
"		this.targetElement = jsc.node(targetElement);\n"\
"		if (!this.targetElement) {\n"\
"			// temporarily customized error message to help with migrating from versions prior to 2.2\n"\
"			if (typeof targetElement === 'string' && /^[a-zA-Z][\\W:.-]*$/.test(targetElement)) {\n"\
"				// targetElement looks like valid ID\n"\
"				var possiblyId = targetElement;\n"\
"				throw new Error('If \\'' + possiblyId + '\\' is supposed to be an ID, please use \\'#' + possiblyId + '\\' or any valid CSS selector.');\n"\
"			}\n"\
"			throw new Error('Cannot instantiate color picker without a target element');\n"\
"		}\n"\
"		if (this.targetElement.jscolor && this.targetElement.jscolor instanceof jsc.pub) {\n"\
"			throw new Error('Color picker already installed on this element');\n"\
"		}\n"\
"		// link this instance with the target element\n"\
"		this.targetElement.jscolor = this;\n"\
"		jsc.addClass(this.targetElement, jsc.pub.className);\n"\
"		// register this instance\n"\
"		jsc.instances.push(this);\n"\
"		// if target is BUTTON\n"\
"		if (jsc.isButton(this.targetElement)) {\n"\
"			if (this.targetElement.type.toLowerCase() !== 'button') {\n"\
"				// on buttons, always force type to be 'button', e.g. in situations the target <button> has no type\n"\
"				// and thus defaults to 'submit' and would submit the form when clicked\n"\
"				this.targetElement.type = 'button';\n"\
"			}\n"\
"			if (jsc.isButtonEmpty(this.targetElement)) { // empty button\n"\
"				// it is important to clear element's contents first.\n"\
"				// if we're re-instantiating color pickers on DOM that has been modified by changing page's innerHTML,\n"\
"				// we would keep adding more non-breaking spaces to element's content (because element's contents survive\n"\
"				// innerHTML changes, but picker instances don't)\n"\
"				jsc.removeChildren(this.targetElement);\n"\
"				// let's insert a non-breaking space\n"\
"				this.targetElement.appendChild(window.document.createTextNode('\xa0'));\n"\
"				// set min-width = previewSize, if not already greater\n"\
"				var compStyle = jsc.getCompStyle(this.targetElement);\n"\
"				var currMinWidth = parseFloat(compStyle['min-width']) || 0;\n"\
"				if (currMinWidth < this.previewSize) {\n"\
"					jsc.setStyle(this.targetElement, {\n"\
"						'min-width': this.previewSize + 'px',\n"\
"					}, this.forceStyle);\n"\
"				}\n"\
"			}\n"\
"		}\n"\
"		// Determine the value element\n"\
"		if (this.valueElement === undefined) {\n"\
"			if (jsc.isTextInput(this.targetElement)) {\n"\
"				// for text inputs, default valueElement is targetElement\n"\
"				this.valueElement = this.targetElement;\n"\
"			} else {\n"\
"				// leave it undefined\n"\
"			}\n"\
"		} else if (this.valueElement === null) { // explicitly set to null\n"\
"			// leave it null\n"\
"		} else { // explicitly set to custom element\n"\
"			this.valueElement = jsc.node(this.valueElement);\n"\
"		}\n"\
"		// Determine the alpha element\n"\
"		if (this.alphaElement) {\n"\
"			this.alphaElement = jsc.node(this.alphaElement);\n"\
"		}\n"\
"		// Determine the preview element\n"\
"		if (this.previewElement === undefined) {\n"\
"			this.previewElement = this.targetElement; // default previewElement is targetElement\n"\
"		} else if (this.previewElement === null) { // explicitly set to null\n"\
"			// leave it null\n"\
"		} else { // explicitly set to custom element\n"\
"			this.previewElement = jsc.node(this.previewElement);\n"\
"		}\n"\
"		// valueElement\n"\
"		if (this.valueElement && jsc.isTextInput(this.valueElement)) {\n"\
"			// If the value element has onInput event already set, we need to detach it and attach AFTER our listener.\n"\
"			// otherwise the picker instance would still contain the old color when accessed from the onInput handler.\n"\
"			var valueElementOrigEvents = {\n"\
"				onInput: this.valueElement.oninput\n"\
"			};\n"\
"			this.valueElement.oninput = null;\n"\
"			this.valueElement.addEventListener('keydown', onValueKeyDown, false);\n"\
"			this.valueElement.addEventListener('change', onValueChange, false);\n"\
"			this.valueElement.addEventListener('input', onValueInput, false);\n"\
"			// the original event listener must be attached AFTER our handler (to let it first set picker's color)\n"\
"			if (valueElementOrigEvents.onInput) {\n"\
"				this.valueElement.addEventListener('input', valueElementOrigEvents.onInput, false);\n"\
"			}\n"\
"			this.valueElement.setAttribute('autocomplete', 'off');\n"\
"			this.valueElement.setAttribute('autocorrect', 'off');\n"\
"			this.valueElement.setAttribute('autocapitalize', 'off');\n"\
"			this.valueElement.setAttribute('spellcheck', false);\n"\
"		}\n"\
"		// alphaElement\n"\
"		if (this.alphaElement && jsc.isTextInput(this.alphaElement)) {\n"\
"			this.alphaElement.addEventListener('keydown', onAlphaKeyDown, false);\n"\
"			this.alphaElement.addEventListener('change', onAlphaChange, false);\n"\
"			this.alphaElement.addEventListener('input', onAlphaInput, false);\n"\
"			this.alphaElement.setAttribute('autocomplete', 'off');\n"\
"			this.alphaElement.setAttribute('autocorrect', 'off');\n"\
"			this.alphaElement.setAttribute('autocapitalize', 'off');\n"\
"			this.alphaElement.setAttribute('spellcheck', false);\n"\
"		}\n"\
"		// determine initial color value\n"\
"		//\n"\
"		var initValue = 'FFFFFF';\n"\
"		if (this.value !== undefined) {\n"\
"			initValue = this.value; // get initial color from the 'value' property\n"\
"		} else if (this.valueElement && this.valueElement.value !== undefined) {\n"\
"			initValue = this.valueElement.value; // get initial color from valueElement's value\n"\
"		}\n"\
"		// determine initial alpha value\n"\
"		//\n"\
"		var initAlpha = undefined;\n"\
"		if (this.alpha !== undefined) {\n"\
"			initAlpha = (''+this.alpha); // get initial alpha value from the 'alpha' property\n"\
"		} else if (this.alphaElement && this.alphaElement.value !== undefined) {\n"\
"			initAlpha = this.alphaElement.value; // get initial color from alphaElement's value\n"\
"		}\n"\
"		// determine current format based on the initial color value\n"\
"		//\n"\
"		this._currentFormat = null;\n"\
"		if (['auto', 'any'].indexOf(this.format.toLowerCase()) > -1) {\n"\
"			// format is 'auto' or 'any' -> let's auto-detect current format\n"\
"			var color = jsc.parseColorString(initValue);\n"\
"			this._currentFormat = color ? color.format : 'hex';\n"\
"		} else {\n"\
"			// format is specified\n"\
"			this._currentFormat = this.format.toLowerCase();\n"\
"		}\n"\
"		// let's parse the initial color value and expose color's preview\n"\
"		this.processValueInput(initValue);\n"\
"		// let's also parse and expose the initial alpha value, if any\n"\
"		//\n"\
"		// Note: If the initial color value contains alpha value in it (e.g. in rgba format),\n"\
"		// this will overwrite it. So we should only process alpha input if there was initial\n"\
"		// alpha explicitly set, otherwise we could needlessly lose initial value's alpha\n"\
"		if (initAlpha !== undefined) {\n"\
"			this.processAlphaInput(initAlpha);\n"\
"		}\n"\
"		if (this.random) {\n"\
"			// randomize the initial color value\n"\
"			this.randomize.apply(this, Array.isArray(this.random) ? this.random : []);\n"\
"		}\n"\
"	}\n"\
"};\n"\
"//================================\n"\
"// Public properties and methods\n"\
"//================================\n"\
"//\n"\
"// These will be publicly available via jscolor.<name> and JSColor.<name>\n"\
"//\n"\
"// class that will be set to elements having jscolor installed on them\n"\
"jsc.pub.className = 'jscolor';\n"\
"// class that will be set to elements having jscolor active on them\n"\
"jsc.pub.activeClassName = 'jscolor-active';\n"\
"// whether to try to parse the options string by evaluating it using 'new Function()'\n"\
"// in case it could not be parsed with JSON.parse()\n"\
"jsc.pub.looseJSON = true;\n"\
"// presets\n"\
"jsc.pub.presets = {};\n"\
"// built-in presets\n"\
"jsc.pub.presets['default'] = {}; // baseline for customization\n"\
"jsc.pub.presets['light'] = { // default color scheme\n"\
"	backgroundColor: 'rgba(255,255,255,1)',\n"\
"	controlBorderColor: 'rgba(187,187,187,1)',\n"\
"	buttonColor: 'rgba(0,0,0,1)',\n"\
"};\n"\
"jsc.pub.presets['dark'] = {\n"\
"	backgroundColor: 'rgba(51,51,51,1)',\n"\
"	controlBorderColor: 'rgba(153,153,153,1)',\n"\
"	buttonColor: 'rgba(240,240,240,1)',\n"\
"};\n"\
"jsc.pub.presets['small'] = { width:101, height:101, padding:10, sliderSize:14, paletteCols:8 };\n"\
"jsc.pub.presets['medium'] = { width:181, height:101, padding:12, sliderSize:16, paletteCols:10 }; // default size\n"\
"jsc.pub.presets['large'] = { width:271, height:151, padding:12, sliderSize:24, paletteCols:15 };\n"\
"jsc.pub.presets['thin'] = { borderWidth:1, controlBorderWidth:1, pointerBorderWidth:1 }; // default thickness\n"\
"jsc.pub.presets['thick'] = { borderWidth:2, controlBorderWidth:2, pointerBorderWidth:2 };\n"\
"// size of space in the sliders\n"\
"jsc.pub.sliderInnerSpace = 3; // px\n"\
"// transparency chessboard\n"\
"jsc.pub.chessboardSize = 8; // px\n"\
"jsc.pub.chessboardColor1 = '#666666';\n"\
"jsc.pub.chessboardColor2 = '#999999';\n"\
"// preview separator\n"\
"jsc.pub.previewSeparator = ['rgba(255,255,255,.65)', 'rgba(128,128,128,.65)'];\n"\
"// Initializes jscolor\n"\
"jsc.pub.init = function () {\n"\
"	if (jsc.initialized) {\n"\
"		return;\n"\
"	}\n"\
"	// attach some necessary handlers\n"\
"	window.document.addEventListener('mousedown', jsc.onDocumentMouseDown, false);\n"\
"	window.document.addEventListener('keyup', jsc.onDocumentKeyUp, false);\n"\
"	window.addEventListener('resize', jsc.onWindowResize, false);\n"\
"	window.addEventListener('scroll', jsc.onWindowScroll, false);\n"\
"	// install jscolor on current DOM\n"\
"	jsc.pub.install();\n"\
"	jsc.initialized = true;\n"\
"	// call functions waiting in the queue\n"\
"	while (jsc.readyQueue.length) {\n"\
"		var func = jsc.readyQueue.shift();\n"\
"		func();\n"\
"	}\n"\
"};\n"\
"// Installs jscolor on current DOM tree\n"\
"jsc.pub.install = function (rootNode) {\n"\
"	var success = true;\n"\
"	try {\n"\
"		jsc.installBySelector('[data-jscolor]', rootNode);\n"\
"	} catch (e) {\n"\
"		success = false;\n"\
"		console.warn(e);\n"\
"	}\n"\
"	// for backward compatibility with DEPRECATED installation using class name\n"\
"	if (jsc.pub.lookupClass) {\n"\
"		try {\n"\
"			jsc.installBySelector(\n"\
"				(\n"\
"					'input.' + jsc.pub.lookupClass + ', ' +\n"\
"					'button.' + jsc.pub.lookupClass\n"\
"				),\n"\
"				rootNode\n"\
"			);\n"\
"		} catch (e) {}\n"\
"	}\n"\
"	return success;\n"\
"};\n"\
"// Registers function to be called as soon as jscolor is initialized (or immediately, if it already is).\n"\
"//\n"\
"jsc.pub.ready = function (func) {\n"\
"	if (typeof func !== 'function') {\n"\
"		console.warn('Passed value is not a function');\n"\
"		return false;\n"\
"	}\n"\
"	if (jsc.initialized) {\n"\
"		func();\n"\
"	} else {\n"\
"		jsc.readyQueue.push(func);\n"\
"	}\n"\
"	return true;\n"\
"};\n"\
"// Triggers given input event(s) (e.g. 'input' or 'change') on all color pickers.\n"\
"//\n"\
"// It is possible to specify multiple events separated with a space.\n"\
"// If called before jscolor is initialized, then the events will be triggered after initialization.\n"\
"//\n"\
"jsc.pub.trigger = function (eventNames) {\n"\
"	var triggerNow = function () {\n"\
"		jsc.triggerGlobal(eventNames);\n"\
"	};\n"\
"	if (jsc.initialized) {\n"\
"		triggerNow();\n"\
"	} else {\n"\
"		jsc.pub.ready(triggerNow);\n"\
"	}\n"\
"};\n"\
"// Hides current color picker box\n"\
"jsc.pub.hide = function () {\n"\
"	if (jsc.picker && jsc.picker.owner) {\n"\
"		jsc.picker.owner.hide();\n"\
"	}\n"\
"};\n"\
"// Returns a data URL of a gray chessboard image that indicates transparency\n"\
"jsc.pub.chessboard = function (color) {\n"\
"	if (!color) {\n"\
"		color = 'rgba(0,0,0,0)';\n"\
"	}\n"\
"	var preview = jsc.genColorPreviewCanvas(color);\n"\
"	return preview.canvas.toDataURL();\n"\
"};\n"\
"// Returns a data URL of a gray chessboard image that indicates transparency\n"\
"jsc.pub.background = function (color) {\n"\
"	var backgrounds = [];\n"\
"	// CSS gradient for background color preview\n"\
"	backgrounds.push(jsc.genColorPreviewGradient(color));\n"\
"	// data URL of generated PNG image with a gray transparency chessboard\n"\
"	var preview = jsc.genColorPreviewCanvas();\n"\
"	backgrounds.push([\n"\
"		'url(\\'' + preview.canvas.toDataURL() + '\\')',\n"\
"		'left top',\n"\
"		'repeat',\n"\
"	].join(' '));\n"\
"	return backgrounds.join(', ');\n"\
"};\n"\
"//\n"\
"// DEPRECATED properties and methods\n"\
"//\n"\
"// DEPRECATED. Use jscolor.presets.default instead.\n"\
"//\n"\
"// Custom default options for all color pickers, e.g. { hash: true, width: 300 }\n"\
"jsc.pub.options = {};\n"\
"// DEPRECATED. Use data-jscolor attribute instead, which installs jscolor on given element.\n"\
"//\n"\
"// By default, we'll search for all elements with class='jscolor' and install a color picker on them.\n"\
"//\n"\
"// You can change what class name will be looked for by setting the property jscolor.lookupClass\n"\
"// anywhere in your HTML document. To completely disable the automatic lookup, set it to null.\n"\
"//\n"\
"jsc.pub.lookupClass = 'jscolor';\n"\
"// DEPRECATED. Use data-jscolor attribute instead, which installs jscolor on given element.\n"\
"//\n"\
"// Install jscolor on all elements that have the specified class name\n"\
"jsc.pub.installByClassName = function () {\n"\
"	console.error('jscolor.installByClassName() is DEPRECATED. Use data-jscolor="" attribute instead of a class name.' + jsc.docsRef);\n"\
"	return false;\n"\
"};\n"\
"jsc.register();\n"\
"return jsc.pub;\n"\
"})(); // END jscolor\n"\
"if (typeof window.jscolor === 'undefined') {\n"\
"	window.jscolor = window.JSColor = jscolor;\n"\
"}\n"\
"// END jscolor code\n"\
"return jscolor;\n"\
"}); // END factory\n"\

