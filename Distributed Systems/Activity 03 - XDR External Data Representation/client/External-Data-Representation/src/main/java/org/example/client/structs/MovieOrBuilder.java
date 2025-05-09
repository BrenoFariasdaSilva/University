// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: movies.proto

package org.example.client.structs;

public interface MovieOrBuilder extends
    // @@protoc_insertion_point(interface_extends:Movie)
    com.google.protobuf.MessageOrBuilder {

  /**
   * <code>string id = 1;</code>
   * @return The id.
   */
  java.lang.String getId();
  /**
   * <code>string id = 1;</code>
   * @return The bytes for id.
   */
  com.google.protobuf.ByteString
      getIdBytes();

  /**
   * <code>string plot = 2;</code>
   * @return The plot.
   */
  java.lang.String getPlot();
  /**
   * <code>string plot = 2;</code>
   * @return The bytes for plot.
   */
  com.google.protobuf.ByteString
      getPlotBytes();

  /**
   * <code>string genre = 3;</code>
   * @return The genre.
   */
  java.lang.String getGenre();
  /**
   * <code>string genre = 3;</code>
   * @return The bytes for genre.
   */
  com.google.protobuf.ByteString
      getGenreBytes();

  /**
   * <code>int32 runtime = 4;</code>
   * @return The runtime.
   */
  int getRuntime();

  /**
   * <code>repeated string cast = 5;</code>
   * @return A list containing the cast.
   */
  java.util.List<java.lang.String>
      getCastList();
  /**
   * <code>repeated string cast = 5;</code>
   * @return The count of cast.
   */
  int getCastCount();
  /**
   * <code>repeated string cast = 5;</code>
   * @param index The index of the element to return.
   * @return The cast at the given index.
   */
  java.lang.String getCast(int index);
  /**
   * <code>repeated string cast = 5;</code>
   * @param index The index of the value to return.
   * @return The bytes of the cast at the given index.
   */
  com.google.protobuf.ByteString
      getCastBytes(int index);

  /**
   * <code>int32 num_mflix_comments = 6;</code>
   * @return The numMflixComments.
   */
  int getNumMflixComments();

  /**
   * <code>string title = 7;</code>
   * @return The title.
   */
  java.lang.String getTitle();
  /**
   * <code>string title = 7;</code>
   * @return The bytes for title.
   */
  com.google.protobuf.ByteString
      getTitleBytes();

  /**
   * <code>string fullplot = 8;</code>
   * @return The fullplot.
   */
  java.lang.String getFullplot();
  /**
   * <code>string fullplot = 8;</code>
   * @return The bytes for fullplot.
   */
  com.google.protobuf.ByteString
      getFullplotBytes();

  /**
   * <code>repeated string countries = 9;</code>
   * @return A list containing the countries.
   */
  java.util.List<java.lang.String>
      getCountriesList();
  /**
   * <code>repeated string countries = 9;</code>
   * @return The count of countries.
   */
  int getCountriesCount();
  /**
   * <code>repeated string countries = 9;</code>
   * @param index The index of the element to return.
   * @return The countries at the given index.
   */
  java.lang.String getCountries(int index);
  /**
   * <code>repeated string countries = 9;</code>
   * @param index The index of the value to return.
   * @return The bytes of the countries at the given index.
   */
  com.google.protobuf.ByteString
      getCountriesBytes(int index);

  /**
   * <code>string released = 10;</code>
   * @return The released.
   */
  java.lang.String getReleased();
  /**
   * <code>string released = 10;</code>
   * @return The bytes for released.
   */
  com.google.protobuf.ByteString
      getReleasedBytes();

  /**
   * <code>repeated string directors = 11;</code>
   * @return A list containing the directors.
   */
  java.util.List<java.lang.String>
      getDirectorsList();
  /**
   * <code>repeated string directors = 11;</code>
   * @return The count of directors.
   */
  int getDirectorsCount();
  /**
   * <code>repeated string directors = 11;</code>
   * @param index The index of the element to return.
   * @return The directors at the given index.
   */
  java.lang.String getDirectors(int index);
  /**
   * <code>repeated string directors = 11;</code>
   * @param index The index of the value to return.
   * @return The bytes of the directors at the given index.
   */
  com.google.protobuf.ByteString
      getDirectorsBytes(int index);

  /**
   * <code>string rated = 12;</code>
   * @return The rated.
   */
  java.lang.String getRated();
  /**
   * <code>string rated = 12;</code>
   * @return The bytes for rated.
   */
  com.google.protobuf.ByteString
      getRatedBytes();

  /**
   * <code>string lastupdated = 13;</code>
   * @return The lastupdated.
   */
  java.lang.String getLastupdated();
  /**
   * <code>string lastupdated = 13;</code>
   * @return The bytes for lastupdated.
   */
  com.google.protobuf.ByteString
      getLastupdatedBytes();

  /**
   * <code>int32 year = 14;</code>
   * @return The year.
   */
  int getYear();

  /**
   * <code>string type = 15;</code>
   * @return The type.
   */
  java.lang.String getType();
  /**
   * <code>string type = 15;</code>
   * @return The bytes for type.
   */
  com.google.protobuf.ByteString
      getTypeBytes();
}
