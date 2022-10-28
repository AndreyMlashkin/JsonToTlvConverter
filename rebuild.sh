REPO_PATH=".."
conan install $REPO_PATH --install-folder=build --build missing && \
conan build   $REPO_PATH --build-folder=build --source-folder=${REPO_PATH} && \
conan package $REPO_PATH --build-folder=build --package-folder=bin
