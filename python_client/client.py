import grpc
import tmax_pb2_grpc as pb2_grpc
import tmax_pb2 as pb2


class ClimateClient(object):
    """
    Client for gRPC functionality
    """

    def __init__(self):
        self.host = 'localhost'
        self.server_port = 50051

        # instantiate a channel
        self.channel = grpc.insecure_channel(
            '{}:{}'.format(self.host, self.server_port))

        # bind the client and the server
        self.stub = pb2_grpc.TmaxStub(self.channel)

    def get_value(self):
        date_location = pb2.DateLocation(days_since_start=0, latitude=40.0, longitude=1.0)
        return self.stub.GetValue(date_location)

    def get_serie(self):
        location = pb2.Location(latitude=40.0, longitude=1.0)
        return self.stub.GetTemperatures(location)

if __name__ == '__main__':
    client = ClimateClient()
    result = client.get_value()
    print(f"GetValue: {result} type: {type(result)} {result.value}")

    result = client.get_serie()

    import timeit
    start = timeit.default_timer()

    t = 0
    for el in result:
        # t += el.value
        t += 1
        # print(f"el = {el.value}")

    print(f"t = {t}")

    stop = timeit.default_timer()
    print("{}s".format(stop - start))
