// This requiew node.js 24+ or Chrome 134+
// This file cannot be excuted on the default settings.


// //Like const, variables declared with using must be initialized and cannot be reassigned. 
// // The variable's value must be either null, undefined, or an object with a [Symbol.dispose]() method.
// // For our use for the management, we will introduce [Symbol.dispose]()
// class Resource {
//     value = Math.random();
//     #isDisposed = false;

//     getValue() {
//         if (this.#isDisposed) {
//             throw new Error("Resource is disposed");
//         }
//         return this.value;
//     }

//     [Symbol.dispose]() {
//         this.#isDisposed = true;
//         console.log("Resource disposed");
//     }
//     using resource = new Resource();
//     console.log(resource.getValue());
//     // resource disposed here
// }
// ///
// // You can use using in the initializer of a for...of loop. 
// // In this case, the resource is disposed on every loop iteration.
// {
//     class Resource {
//         value = Math.random();
//         [Symbol.dispose]() {
//             console.log("Resource disposed");
//         }
//     }
//     const resources = [new Resource(), new Resource(), new Resource()];

//     for (using resource of resources) {
//         console.log(resource.value);
//     }
// }