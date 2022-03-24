The assumption for platform driver was to build it as a library.

In the root CMakeLists.txt you can choose to also build an application mock which can
be used to test the library.

Getting started:
1. run "mkdir build && cd build"
2. run "cmake -S ../ -B ."
3. run "cmake --build ."

Now you should see the outputs under build/ folder.

To run unit tests:
1. Make sure you enabled unit tests from root CmakeLists.txt
2. Make sure you followed "Getting Started" instructions
3. Run "ctest"

If you want to test the library:
1. Enable building with mock from root CMakeLists.txt
2. Follow "Getting started" instructions
3. Open a new terminal from the same directory
4. Run "./application_mock/fan_controller_app_mock"
5. Run "cd ../tcp_client"
6. Run "python3 python-client.py"
7. The client should now be connected to the TCP server
8. Client will prompt for you to insert any command