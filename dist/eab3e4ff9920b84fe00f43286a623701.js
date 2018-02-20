// modules are defined as an array
// [ module function, map of requires ]
//
// map of requires is short require name -> numeric require
//
// anything defined in a previous bundle is accessed via the
// orig method which is the require for previous bundles

// eslint-disable-next-line no-global-assign
require = (function (modules, cache, entry) {
  // Save the require from previous bundle to this closure if any
  var previousRequire = typeof require === "function" && require;

  function newRequire(name, jumped) {
    if (!cache[name]) {
      if (!modules[name]) {
        // if we cannot find the module within our internal map or
        // cache jump to the current global require ie. the last bundle
        // that was added to the page.
        var currentRequire = typeof require === "function" && require;
        if (!jumped && currentRequire) {
          return currentRequire(name, true);
        }

        // If there are other bundles on this page the require from the
        // previous one is saved to 'previousRequire'. Repeat this as
        // many times as there are bundles until the module is found or
        // we exhaust the require chain.
        if (previousRequire) {
          return previousRequire(name, true);
        }

        var err = new Error('Cannot find module \'' + name + '\'');
        err.code = 'MODULE_NOT_FOUND';
        throw err;
      }

      localRequire.resolve = resolve;

      var module = cache[name] = new newRequire.Module(name);

      modules[name][0].call(module.exports, localRequire, module, module.exports);
    }

    return cache[name].exports;

    function localRequire(x){
      return newRequire(localRequire.resolve(x));
    }

    function resolve(x){
      return modules[name][1][x] || x;
    }
  }

  function Module(moduleName) {
    this.id = moduleName;
    this.bundle = newRequire;
    this.exports = {};
  }

  newRequire.isParcelRequire = true;
  newRequire.Module = Module;
  newRequire.modules = modules;
  newRequire.cache = cache;
  newRequire.parent = previousRequire;

  for (var i = 0; i < entry.length; i++) {
    newRequire(entry[i]);
  }

  // Override the current require with this new one
  return newRequire;
})({4:[function(require,module,exports) {
function normalizeArray(parts, allowAboveRoot) {
  // if the path tries to go above the root, `up` ends up > 0
  var up = 0;
  for (var i = parts.length - 1; i >= 0; i--) {
    var last = parts[i];
    if (last === '.') {
      parts.splice(i, 1);
    } else if (last === '..') {
      parts.splice(i, 1);
      up++;
    } else if (up) {
      parts.splice(i, 1);
      up--;
    }
  }

  // if the path is allowed to go above the root, restore leading ..s
  if (allowAboveRoot) {
    for (; up--; up) {
      parts.unshift('..');
    }
  }

  return parts;
};

function pathNormalize(path) {
  var isAbsolute = path.charAt(0) === '/';
  var trailingSlash = path.substr(-1) === '/';

  // Normalize the path
  path = normalizeArray(path.split('/').filter(function (p) {
    return !!p;
  }), !isAbsolute).join('/');

  if (!path && !isAbsolute) {
    path = '.';
  }
  if (path && trailingSlash) {
    path += '/';
  }

  return (isAbsolute ? '/' : '') + path;
};

var globalEval = eval;
var currentScript = document.currentScript;
var projectRoot = currentScript.dataset['project-root'] || currentScript.dataset['projectRoot'];
if (projectRoot == null) {
  throw new Error('The attribute `data-project-root` isn\'t found in the script tag. You need to provide the root (in which node_modules reside).');
}
var nodeModulesDir = projectRoot + '/node_modules/';

var modulesCache = {};
var packageJsonMainCache = {};

var ensureEndsWithJs = function ensureEndsWithJs(path) {
  if (path.endsWith('.js')) {
    return path;
  } else {
    return path + '.js';
  }
};
function loadScript(scriptPath) {
  var request = new XMLHttpRequest();

  request.open("GET", scriptPath, false); // sync
  request.send();
  var dirSeparatorIndex = scriptPath.lastIndexOf('/');
  var dir = dirSeparatorIndex === -1 ? '.' : scriptPath.slice(0, dirSeparatorIndex);

  var moduleText = '\n(function(module, exports, modulesCache, packageJsonMainCache, nodeModulesDir) {\n  function require(path) {\n    var __dirname = "' + dir + '/";\n    var resolvedPath;\n    if (path.startsWith(\'.\')) {\n      // require(\'./foo/bar\')\n      resolvedPath = ensureEndsWithJs(__dirname + path);\n    } else if (path.indexOf(\'/\') === -1) {\n      // require(\'react\')\n      var packageJson = pathNormalize(nodeModulesDir + path + \'/package.json\');\n      if (packageJsonMainCache[packageJson] == null) {\n        var jsonRequest = new XMLHttpRequest();\n        jsonRequest.open("GET", packageJson, false);\n        jsonRequest.send();\n        var main;\n        if (jsonRequest.responseText != null) {\n          main = JSON.parse(jsonRequest.responseText).main;\n        };\n        if (main == null) {\n          main = \'index.js\';\n        } else if (!main.endsWith(\'.js\')) {\n          main = main + \'.js\';\n        }\n        packageJsonMainCache[packageJson] = nodeModulesDir + path + \'/\' + main;\n      }\n      resolvedPath = packageJsonMainCache[packageJson];\n    } else {\n      // require(\'react/bar\')\n      resolvedPath = ensureEndsWithJs(nodeModulesDir + path);\n    };\n    resolvedPath = pathNormalize(resolvedPath);\n    if (modulesCache[resolvedPath] != null) {\n      return modulesCache[resolvedPath];\n    };\n    var result = loadScript(resolvedPath);\n    modulesCache[resolvedPath] = result;\n    return result;\n  };\n  var process = {env: {}, argv: []};\n  var global = {};\n\n\n// -------Begin Require Polyfilled Module Loaded From Disk------------------------------\n// file: ' + scriptPath + '\n// root: ' + projectRoot + '\n// ----------------------------------------------------------------------\n' + request.responseText + '\n// -------End Polyfill Loaded From Disk------------------------------\n// file: ' + scriptPath + '\n// root: ' + projectRoot + '\n// ----------------------------------------------------------------------\nreturn module.exports})\n//@ sourceURL=' + scriptPath;
  var module = { exports: {} };
  return globalEval(moduleText)(module, module.exports, modulesCache, packageJsonMainCache, nodeModulesDir);
};

loadScript(currentScript.dataset.main);
},{}],6:[function(require,module,exports) {

var global = (1, eval)('this');
var OldModule = module.bundle.Module;
function Module(moduleName) {
  OldModule.call(this, moduleName);
  this.hot = {
    accept: function (fn) {
      this._acceptCallback = fn || function () {};
    },
    dispose: function (fn) {
      this._disposeCallback = fn;
    }
  };
}

module.bundle.Module = Module;

var parent = module.bundle.parent;
if ((!parent || !parent.isParcelRequire) && typeof WebSocket !== 'undefined') {
  var hostname = '' || location.hostname;
  var protocol = location.protocol === 'https:' ? 'wss' : 'ws';
  var ws = new WebSocket(protocol + '://' + hostname + ':' + '54565' + '/');
  ws.onmessage = function (event) {
    var data = JSON.parse(event.data);

    if (data.type === 'update') {
      data.assets.forEach(function (asset) {
        hmrApply(global.require, asset);
      });

      data.assets.forEach(function (asset) {
        if (!asset.isNew) {
          hmrAccept(global.require, asset.id);
        }
      });
    }

    if (data.type === 'reload') {
      ws.close();
      ws.onclose = function () {
        location.reload();
      };
    }

    if (data.type === 'error-resolved') {
      console.log('[parcel] ✨ Error resolved');
    }

    if (data.type === 'error') {
      console.error('[parcel] 🚨  ' + data.error.message + '\n' + 'data.error.stack');
    }
  };
}

function getParents(bundle, id) {
  var modules = bundle.modules;
  if (!modules) {
    return [];
  }

  var parents = [];
  var k, d, dep;

  for (k in modules) {
    for (d in modules[k][1]) {
      dep = modules[k][1][d];
      if (dep === id || Array.isArray(dep) && dep[dep.length - 1] === id) {
        parents.push(+k);
      }
    }
  }

  if (bundle.parent) {
    parents = parents.concat(getParents(bundle.parent, id));
  }

  return parents;
}

function hmrApply(bundle, asset) {
  var modules = bundle.modules;
  if (!modules) {
    return;
  }

  if (modules[asset.id] || !bundle.parent) {
    var fn = new Function('require', 'module', 'exports', asset.generated.js);
    asset.isNew = !modules[asset.id];
    modules[asset.id] = [fn, asset.deps];
  } else if (bundle.parent) {
    hmrApply(bundle.parent, asset);
  }
}

function hmrAccept(bundle, id) {
  var modules = bundle.modules;
  if (!modules) {
    return;
  }

  if (!modules[id] && bundle.parent) {
    return hmrAccept(bundle.parent, id);
  }

  var cached = bundle.cache[id];
  if (cached && cached.hot._disposeCallback) {
    cached.hot._disposeCallback();
  }

  delete bundle.cache[id];
  bundle(id);

  cached = bundle.cache[id];
  if (cached && cached.hot && cached.hot._acceptCallback) {
    cached.hot._acceptCallback();
    return true;
  }

  return getParents(global.require, id).some(function (id) {
    return hmrAccept(global.require, id);
  });
}
},{}]},{},[6,4])
//# sourceMappingURL=/dist/eab3e4ff9920b84fe00f43286a623701.map