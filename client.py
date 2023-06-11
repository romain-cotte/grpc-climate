import grpc
import tmax_pb2_grpc as pb2_grpc
import tmax_pb2 as pb2


class TmaxClient(object):
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
        """
        Client function to call the rpc for GetServerResponse
        """
        date_location = pb2.DateLocation(
            days_since_start=1,
            latitude=2,
            longitude=3
        )
        print(f'{date_location}')
        return self.stub.GetValue(date_location)


if __name__ == '__main__':
    client = TmaxClient()
    result = client.get_value()
    print(f"Result: {result.value}")
