# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

import movies_pb2 as movies__pb2


class MovieServiceStub(object):
    """Missing associated documentation comment in .proto file."""

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.CreateMovie = channel.unary_unary(
                '/moviesPackage.MovieService/CreateMovie',
                request_serializer=movies__pb2.Movie.SerializeToString,
                response_deserializer=movies__pb2.Message.FromString,
                )
        self.GetMovie = channel.unary_unary(
                '/moviesPackage.MovieService/GetMovie',
                request_serializer=movies__pb2.Message.SerializeToString,
                response_deserializer=movies__pb2.Movie.FromString,
                )
        self.UpdateMovie = channel.unary_unary(
                '/moviesPackage.MovieService/UpdateMovie',
                request_serializer=movies__pb2.Movie.SerializeToString,
                response_deserializer=movies__pb2.Message.FromString,
                )
        self.DeleteMovie = channel.unary_unary(
                '/moviesPackage.MovieService/DeleteMovie',
                request_serializer=movies__pb2.Message.SerializeToString,
                response_deserializer=movies__pb2.Message.FromString,
                )
        self.ListMoviesByActor = channel.unary_unary(
                '/moviesPackage.MovieService/ListMoviesByActor',
                request_serializer=movies__pb2.Message.SerializeToString,
                response_deserializer=movies__pb2.MoviesList.FromString,
                )
        self.ListMoviesByGenre = channel.unary_unary(
                '/moviesPackage.MovieService/ListMoviesByGenre',
                request_serializer=movies__pb2.Message.SerializeToString,
                response_deserializer=movies__pb2.MoviesList.FromString,
                )


class MovieServiceServicer(object):
    """Missing associated documentation comment in .proto file."""

    def CreateMovie(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def GetMovie(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def UpdateMovie(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def DeleteMovie(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def ListMoviesByActor(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def ListMoviesByGenre(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_MovieServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'CreateMovie': grpc.unary_unary_rpc_method_handler(
                    servicer.CreateMovie,
                    request_deserializer=movies__pb2.Movie.FromString,
                    response_serializer=movies__pb2.Message.SerializeToString,
            ),
            'GetMovie': grpc.unary_unary_rpc_method_handler(
                    servicer.GetMovie,
                    request_deserializer=movies__pb2.Message.FromString,
                    response_serializer=movies__pb2.Movie.SerializeToString,
            ),
            'UpdateMovie': grpc.unary_unary_rpc_method_handler(
                    servicer.UpdateMovie,
                    request_deserializer=movies__pb2.Movie.FromString,
                    response_serializer=movies__pb2.Message.SerializeToString,
            ),
            'DeleteMovie': grpc.unary_unary_rpc_method_handler(
                    servicer.DeleteMovie,
                    request_deserializer=movies__pb2.Message.FromString,
                    response_serializer=movies__pb2.Message.SerializeToString,
            ),
            'ListMoviesByActor': grpc.unary_unary_rpc_method_handler(
                    servicer.ListMoviesByActor,
                    request_deserializer=movies__pb2.Message.FromString,
                    response_serializer=movies__pb2.MoviesList.SerializeToString,
            ),
            'ListMoviesByGenre': grpc.unary_unary_rpc_method_handler(
                    servicer.ListMoviesByGenre,
                    request_deserializer=movies__pb2.Message.FromString,
                    response_serializer=movies__pb2.MoviesList.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'moviesPackage.MovieService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))


 # This class is part of an EXPERIMENTAL API.
class MovieService(object):
    """Missing associated documentation comment in .proto file."""

    @staticmethod
    def CreateMovie(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/moviesPackage.MovieService/CreateMovie',
            movies__pb2.Movie.SerializeToString,
            movies__pb2.Message.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def GetMovie(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/moviesPackage.MovieService/GetMovie',
            movies__pb2.Message.SerializeToString,
            movies__pb2.Movie.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def UpdateMovie(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/moviesPackage.MovieService/UpdateMovie',
            movies__pb2.Movie.SerializeToString,
            movies__pb2.Message.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def DeleteMovie(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/moviesPackage.MovieService/DeleteMovie',
            movies__pb2.Message.SerializeToString,
            movies__pb2.Message.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def ListMoviesByActor(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/moviesPackage.MovieService/ListMoviesByActor',
            movies__pb2.Message.SerializeToString,
            movies__pb2.MoviesList.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def ListMoviesByGenre(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/moviesPackage.MovieService/ListMoviesByGenre',
            movies__pb2.Message.SerializeToString,
            movies__pb2.MoviesList.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)