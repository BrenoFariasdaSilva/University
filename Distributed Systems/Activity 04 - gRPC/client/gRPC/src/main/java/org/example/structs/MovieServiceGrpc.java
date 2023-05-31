package org.example.structs;

import static io.grpc.stub.ClientCalls.asyncUnaryCall;
import static io.grpc.stub.ClientCalls.asyncServerStreamingCall;
import static io.grpc.stub.ClientCalls.asyncClientStreamingCall;
import static io.grpc.stub.ClientCalls.asyncBidiStreamingCall;
import static io.grpc.stub.ClientCalls.blockingUnaryCall;
import static io.grpc.stub.ClientCalls.blockingServerStreamingCall;
import static io.grpc.stub.ClientCalls.futureUnaryCall;
import static io.grpc.MethodDescriptor.generateFullMethodName;
import static io.grpc.stub.ServerCalls.asyncUnaryCall;
import static io.grpc.stub.ServerCalls.asyncServerStreamingCall;
import static io.grpc.stub.ServerCalls.asyncClientStreamingCall;
import static io.grpc.stub.ServerCalls.asyncBidiStreamingCall;
import static io.grpc.stub.ServerCalls.asyncUnimplementedUnaryCall;
import static io.grpc.stub.ServerCalls.asyncUnimplementedStreamingCall;

/**
 * <pre>
 * The service definition, which contains the RPCs, arguments, and return types
 * </pre>
 */
@javax.annotation.Generated(
    value = "by gRPC proto compiler (version 1.4.0)",
    comments = "Source: movies.proto")
public final class MovieServiceGrpc {

  private MovieServiceGrpc() {}

  public static final String SERVICE_NAME = "moviesPackage.MovieService";

  // Static method descriptors that strictly reflect the proto.
  @io.grpc.ExperimentalApi("https://github.com/grpc/grpc-java/issues/1901")
  public static final io.grpc.MethodDescriptor<org.example.structs.Movie,
      org.example.structs.Message> METHOD_CREATE_MOVIE =
      io.grpc.MethodDescriptor.<org.example.structs.Movie, org.example.structs.Message>newBuilder()
          .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
          .setFullMethodName(generateFullMethodName(
              "moviesPackage.MovieService", "CreateMovie"))
          .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
              org.example.structs.Movie.getDefaultInstance()))
          .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
              org.example.structs.Message.getDefaultInstance()))
          .build();
  @io.grpc.ExperimentalApi("https://github.com/grpc/grpc-java/issues/1901")
  public static final io.grpc.MethodDescriptor<org.example.structs.Message,
      org.example.structs.Movie> METHOD_GET_MOVIE =
      io.grpc.MethodDescriptor.<org.example.structs.Message, org.example.structs.Movie>newBuilder()
          .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
          .setFullMethodName(generateFullMethodName(
              "moviesPackage.MovieService", "GetMovie"))
          .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
              org.example.structs.Message.getDefaultInstance()))
          .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
              org.example.structs.Movie.getDefaultInstance()))
          .build();
  @io.grpc.ExperimentalApi("https://github.com/grpc/grpc-java/issues/1901")
  public static final io.grpc.MethodDescriptor<org.example.structs.Movie,
      org.example.structs.Message> METHOD_UPDATE_MOVIE =
      io.grpc.MethodDescriptor.<org.example.structs.Movie, org.example.structs.Message>newBuilder()
          .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
          .setFullMethodName(generateFullMethodName(
              "moviesPackage.MovieService", "UpdateMovie"))
          .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
              org.example.structs.Movie.getDefaultInstance()))
          .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
              org.example.structs.Message.getDefaultInstance()))
          .build();
  @io.grpc.ExperimentalApi("https://github.com/grpc/grpc-java/issues/1901")
  public static final io.grpc.MethodDescriptor<org.example.structs.Message,
      org.example.structs.Message> METHOD_DELETE_MOVIE =
      io.grpc.MethodDescriptor.<org.example.structs.Message, org.example.structs.Message>newBuilder()
          .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
          .setFullMethodName(generateFullMethodName(
              "moviesPackage.MovieService", "DeleteMovie"))
          .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
              org.example.structs.Message.getDefaultInstance()))
          .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
              org.example.structs.Message.getDefaultInstance()))
          .build();
  @io.grpc.ExperimentalApi("https://github.com/grpc/grpc-java/issues/1901")
  public static final io.grpc.MethodDescriptor<org.example.structs.Message,
      org.example.structs.MoviesList> METHOD_LIST_MOVIES_BY_ACTOR =
      io.grpc.MethodDescriptor.<org.example.structs.Message, org.example.structs.MoviesList>newBuilder()
          .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
          .setFullMethodName(generateFullMethodName(
              "moviesPackage.MovieService", "ListMoviesByActor"))
          .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
              org.example.structs.Message.getDefaultInstance()))
          .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
              org.example.structs.MoviesList.getDefaultInstance()))
          .build();
  @io.grpc.ExperimentalApi("https://github.com/grpc/grpc-java/issues/1901")
  public static final io.grpc.MethodDescriptor<org.example.structs.Message,
      org.example.structs.MoviesList> METHOD_LIST_MOVIES_BY_GENRE =
      io.grpc.MethodDescriptor.<org.example.structs.Message, org.example.structs.MoviesList>newBuilder()
          .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
          .setFullMethodName(generateFullMethodName(
              "moviesPackage.MovieService", "ListMoviesByGenre"))
          .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
              org.example.structs.Message.getDefaultInstance()))
          .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
              org.example.structs.MoviesList.getDefaultInstance()))
          .build();

  /**
   * Creates a new async stub that supports all call types for the service
   */
  public static MovieServiceStub newStub(io.grpc.Channel channel) {
    return new MovieServiceStub(channel);
  }

  /**
   * Creates a new blocking-style stub that supports unary and streaming output calls on the service
   */
  public static MovieServiceBlockingStub newBlockingStub(
      io.grpc.Channel channel) {
    return new MovieServiceBlockingStub(channel);
  }

  /**
   * Creates a new ListenableFuture-style stub that supports unary calls on the service
   */
  public static MovieServiceFutureStub newFutureStub(
      io.grpc.Channel channel) {
    return new MovieServiceFutureStub(channel);
  }

  /**
   * <pre>
   * The service definition, which contains the RPCs, arguments, and return types
   * </pre>
   */
  public static abstract class MovieServiceImplBase implements io.grpc.BindableService {

    /**
     */
    public void createMovie(org.example.structs.Movie request,
        io.grpc.stub.StreamObserver<org.example.structs.Message> responseObserver) {
      asyncUnimplementedUnaryCall(METHOD_CREATE_MOVIE, responseObserver);
    }

    /**
     */
    public void getMovie(org.example.structs.Message request,
        io.grpc.stub.StreamObserver<org.example.structs.Movie> responseObserver) {
      asyncUnimplementedUnaryCall(METHOD_GET_MOVIE, responseObserver);
    }

    /**
     */
    public void updateMovie(org.example.structs.Movie request,
        io.grpc.stub.StreamObserver<org.example.structs.Message> responseObserver) {
      asyncUnimplementedUnaryCall(METHOD_UPDATE_MOVIE, responseObserver);
    }

    /**
     */
    public void deleteMovie(org.example.structs.Message request,
        io.grpc.stub.StreamObserver<org.example.structs.Message> responseObserver) {
      asyncUnimplementedUnaryCall(METHOD_DELETE_MOVIE, responseObserver);
    }

    /**
     */
    public void listMoviesByActor(org.example.structs.Message request,
        io.grpc.stub.StreamObserver<org.example.structs.MoviesList> responseObserver) {
      asyncUnimplementedUnaryCall(METHOD_LIST_MOVIES_BY_ACTOR, responseObserver);
    }

    /**
     */
    public void listMoviesByGenre(org.example.structs.Message request,
        io.grpc.stub.StreamObserver<org.example.structs.MoviesList> responseObserver) {
      asyncUnimplementedUnaryCall(METHOD_LIST_MOVIES_BY_GENRE, responseObserver);
    }

    @java.lang.Override public final io.grpc.ServerServiceDefinition bindService() {
      return io.grpc.ServerServiceDefinition.builder(getServiceDescriptor())
          .addMethod(
            METHOD_CREATE_MOVIE,
            asyncUnaryCall(
              new MethodHandlers<
                org.example.structs.Movie,
                org.example.structs.Message>(
                  this, METHODID_CREATE_MOVIE)))
          .addMethod(
            METHOD_GET_MOVIE,
            asyncUnaryCall(
              new MethodHandlers<
                org.example.structs.Message,
                org.example.structs.Movie>(
                  this, METHODID_GET_MOVIE)))
          .addMethod(
            METHOD_UPDATE_MOVIE,
            asyncUnaryCall(
              new MethodHandlers<
                org.example.structs.Movie,
                org.example.structs.Message>(
                  this, METHODID_UPDATE_MOVIE)))
          .addMethod(
            METHOD_DELETE_MOVIE,
            asyncUnaryCall(
              new MethodHandlers<
                org.example.structs.Message,
                org.example.structs.Message>(
                  this, METHODID_DELETE_MOVIE)))
          .addMethod(
            METHOD_LIST_MOVIES_BY_ACTOR,
            asyncUnaryCall(
              new MethodHandlers<
                org.example.structs.Message,
                org.example.structs.MoviesList>(
                  this, METHODID_LIST_MOVIES_BY_ACTOR)))
          .addMethod(
            METHOD_LIST_MOVIES_BY_GENRE,
            asyncUnaryCall(
              new MethodHandlers<
                org.example.structs.Message,
                org.example.structs.MoviesList>(
                  this, METHODID_LIST_MOVIES_BY_GENRE)))
          .build();
    }
  }

  /**
   * <pre>
   * The service definition, which contains the RPCs, arguments, and return types
   * </pre>
   */
  public static final class MovieServiceStub extends io.grpc.stub.AbstractStub<MovieServiceStub> {
    private MovieServiceStub(io.grpc.Channel channel) {
      super(channel);
    }

    private MovieServiceStub(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @java.lang.Override
    protected MovieServiceStub build(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      return new MovieServiceStub(channel, callOptions);
    }

    /**
     */
    public void createMovie(org.example.structs.Movie request,
        io.grpc.stub.StreamObserver<org.example.structs.Message> responseObserver) {
      asyncUnaryCall(
          getChannel().newCall(METHOD_CREATE_MOVIE, getCallOptions()), request, responseObserver);
    }

    /**
     */
    public void getMovie(org.example.structs.Message request,
        io.grpc.stub.StreamObserver<org.example.structs.Movie> responseObserver) {
      asyncUnaryCall(
          getChannel().newCall(METHOD_GET_MOVIE, getCallOptions()), request, responseObserver);
    }

    /**
     */
    public void updateMovie(org.example.structs.Movie request,
        io.grpc.stub.StreamObserver<org.example.structs.Message> responseObserver) {
      asyncUnaryCall(
          getChannel().newCall(METHOD_UPDATE_MOVIE, getCallOptions()), request, responseObserver);
    }

    /**
     */
    public void deleteMovie(org.example.structs.Message request,
        io.grpc.stub.StreamObserver<org.example.structs.Message> responseObserver) {
      asyncUnaryCall(
          getChannel().newCall(METHOD_DELETE_MOVIE, getCallOptions()), request, responseObserver);
    }

    /**
     */
    public void listMoviesByActor(org.example.structs.Message request,
        io.grpc.stub.StreamObserver<org.example.structs.MoviesList> responseObserver) {
      asyncUnaryCall(
          getChannel().newCall(METHOD_LIST_MOVIES_BY_ACTOR, getCallOptions()), request, responseObserver);
    }

    /**
     */
    public void listMoviesByGenre(org.example.structs.Message request,
        io.grpc.stub.StreamObserver<org.example.structs.MoviesList> responseObserver) {
      asyncUnaryCall(
          getChannel().newCall(METHOD_LIST_MOVIES_BY_GENRE, getCallOptions()), request, responseObserver);
    }
  }

  /**
   * <pre>
   * The service definition, which contains the RPCs, arguments, and return types
   * </pre>
   */
  public static final class MovieServiceBlockingStub extends io.grpc.stub.AbstractStub<MovieServiceBlockingStub> {
    private MovieServiceBlockingStub(io.grpc.Channel channel) {
      super(channel);
    }

    private MovieServiceBlockingStub(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @java.lang.Override
    protected MovieServiceBlockingStub build(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      return new MovieServiceBlockingStub(channel, callOptions);
    }

    /**
     */
    public org.example.structs.Message createMovie(org.example.structs.Movie request) {
      return blockingUnaryCall(
          getChannel(), METHOD_CREATE_MOVIE, getCallOptions(), request);
    }

    /**
     */
    public org.example.structs.Movie getMovie(org.example.structs.Message request) {
      return blockingUnaryCall(
          getChannel(), METHOD_GET_MOVIE, getCallOptions(), request);
    }

    /**
     */
    public org.example.structs.Message updateMovie(org.example.structs.Movie request) {
      return blockingUnaryCall(
          getChannel(), METHOD_UPDATE_MOVIE, getCallOptions(), request);
    }

    /**
     */
    public org.example.structs.Message deleteMovie(org.example.structs.Message request) {
      return blockingUnaryCall(
          getChannel(), METHOD_DELETE_MOVIE, getCallOptions(), request);
    }

    /**
     */
    public org.example.structs.MoviesList listMoviesByActor(org.example.structs.Message request) {
      return blockingUnaryCall(
          getChannel(), METHOD_LIST_MOVIES_BY_ACTOR, getCallOptions(), request);
    }

    /**
     */
    public org.example.structs.MoviesList listMoviesByGenre(org.example.structs.Message request) {
      return blockingUnaryCall(
          getChannel(), METHOD_LIST_MOVIES_BY_GENRE, getCallOptions(), request);
    }
  }

  /**
   * <pre>
   * The service definition, which contains the RPCs, arguments, and return types
   * </pre>
   */
  public static final class MovieServiceFutureStub extends io.grpc.stub.AbstractStub<MovieServiceFutureStub> {
    private MovieServiceFutureStub(io.grpc.Channel channel) {
      super(channel);
    }

    private MovieServiceFutureStub(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @java.lang.Override
    protected MovieServiceFutureStub build(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      return new MovieServiceFutureStub(channel, callOptions);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<org.example.structs.Message> createMovie(
        org.example.structs.Movie request) {
      return futureUnaryCall(
          getChannel().newCall(METHOD_CREATE_MOVIE, getCallOptions()), request);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<org.example.structs.Movie> getMovie(
        org.example.structs.Message request) {
      return futureUnaryCall(
          getChannel().newCall(METHOD_GET_MOVIE, getCallOptions()), request);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<org.example.structs.Message> updateMovie(
        org.example.structs.Movie request) {
      return futureUnaryCall(
          getChannel().newCall(METHOD_UPDATE_MOVIE, getCallOptions()), request);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<org.example.structs.Message> deleteMovie(
        org.example.structs.Message request) {
      return futureUnaryCall(
          getChannel().newCall(METHOD_DELETE_MOVIE, getCallOptions()), request);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<org.example.structs.MoviesList> listMoviesByActor(
        org.example.structs.Message request) {
      return futureUnaryCall(
          getChannel().newCall(METHOD_LIST_MOVIES_BY_ACTOR, getCallOptions()), request);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<org.example.structs.MoviesList> listMoviesByGenre(
        org.example.structs.Message request) {
      return futureUnaryCall(
          getChannel().newCall(METHOD_LIST_MOVIES_BY_GENRE, getCallOptions()), request);
    }
  }

  private static final int METHODID_CREATE_MOVIE = 0;
  private static final int METHODID_GET_MOVIE = 1;
  private static final int METHODID_UPDATE_MOVIE = 2;
  private static final int METHODID_DELETE_MOVIE = 3;
  private static final int METHODID_LIST_MOVIES_BY_ACTOR = 4;
  private static final int METHODID_LIST_MOVIES_BY_GENRE = 5;

  private static final class MethodHandlers<Req, Resp> implements
      io.grpc.stub.ServerCalls.UnaryMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.ServerStreamingMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.ClientStreamingMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.BidiStreamingMethod<Req, Resp> {
    private final MovieServiceImplBase serviceImpl;
    private final int methodId;

    MethodHandlers(MovieServiceImplBase serviceImpl, int methodId) {
      this.serviceImpl = serviceImpl;
      this.methodId = methodId;
    }

    @java.lang.Override
    @java.lang.SuppressWarnings("unchecked")
    public void invoke(Req request, io.grpc.stub.StreamObserver<Resp> responseObserver) {
      switch (methodId) {
        case METHODID_CREATE_MOVIE:
          serviceImpl.createMovie((org.example.structs.Movie) request,
              (io.grpc.stub.StreamObserver<org.example.structs.Message>) responseObserver);
          break;
        case METHODID_GET_MOVIE:
          serviceImpl.getMovie((org.example.structs.Message) request,
              (io.grpc.stub.StreamObserver<org.example.structs.Movie>) responseObserver);
          break;
        case METHODID_UPDATE_MOVIE:
          serviceImpl.updateMovie((org.example.structs.Movie) request,
              (io.grpc.stub.StreamObserver<org.example.structs.Message>) responseObserver);
          break;
        case METHODID_DELETE_MOVIE:
          serviceImpl.deleteMovie((org.example.structs.Message) request,
              (io.grpc.stub.StreamObserver<org.example.structs.Message>) responseObserver);
          break;
        case METHODID_LIST_MOVIES_BY_ACTOR:
          serviceImpl.listMoviesByActor((org.example.structs.Message) request,
              (io.grpc.stub.StreamObserver<org.example.structs.MoviesList>) responseObserver);
          break;
        case METHODID_LIST_MOVIES_BY_GENRE:
          serviceImpl.listMoviesByGenre((org.example.structs.Message) request,
              (io.grpc.stub.StreamObserver<org.example.structs.MoviesList>) responseObserver);
          break;
        default:
          throw new AssertionError();
      }
    }

    @java.lang.Override
    @java.lang.SuppressWarnings("unchecked")
    public io.grpc.stub.StreamObserver<Req> invoke(
        io.grpc.stub.StreamObserver<Resp> responseObserver) {
      switch (methodId) {
        default:
          throw new AssertionError();
      }
    }
  }

  private static final class MovieServiceDescriptorSupplier implements io.grpc.protobuf.ProtoFileDescriptorSupplier {
    @java.lang.Override
    public com.google.protobuf.Descriptors.FileDescriptor getFileDescriptor() {
      return org.example.structs.Movies.getDescriptor();
    }
  }

  private static volatile io.grpc.ServiceDescriptor serviceDescriptor;

  public static io.grpc.ServiceDescriptor getServiceDescriptor() {
    io.grpc.ServiceDescriptor result = serviceDescriptor;
    if (result == null) {
      synchronized (MovieServiceGrpc.class) {
        result = serviceDescriptor;
        if (result == null) {
          serviceDescriptor = result = io.grpc.ServiceDescriptor.newBuilder(SERVICE_NAME)
              .setSchemaDescriptor(new MovieServiceDescriptorSupplier())
              .addMethod(METHOD_CREATE_MOVIE)
              .addMethod(METHOD_GET_MOVIE)
              .addMethod(METHOD_UPDATE_MOVIE)
              .addMethod(METHOD_DELETE_MOVIE)
              .addMethod(METHOD_LIST_MOVIES_BY_ACTOR)
              .addMethod(METHOD_LIST_MOVIES_BY_GENRE)
              .build();
        }
      }
    }
    return result;
  }
}
