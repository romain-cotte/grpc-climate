
# Generate the stubs

```sh
python -m grpc_tools.protoc \
  --proto_path=. \
  ./unary.proto \
  --python_out=. \
  --grpc_python_out=.
```

# Request server

```sh
grpcurl -d '{"message": "test"}' \
  -plaintext localhost:8085 unary.Unary/GetServerResponse
```


# Build with buildpack

```sh
pack build test-python-app \
--builder paketobuildpacks/builder:base \
--buildpack "gcr.io/paketo-buildpacks/python"
```

# Run locally

```sh
docker run -d -p 8085:8080 test-python-app
```


# Logs

```sh
flyctl logs -a grpc-python
```


# Try to host this server

```sh
grpcurl -d '{"message": "test"}' grpc-python.fly.dev:443 unary.Unary/GetServerResponse


grpcurl -proto unary.proto grpc-python.fly.dev:443 unary.Unary/GetServerResponse

grpcurl -proto ../../fly/grpc-service/hello.proto fragrant-smoke-7668.fly.dev:443 MainService/Hello

```
